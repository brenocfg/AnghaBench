#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  char WCHAR ;
typedef  int UINT ;
struct TYPE_11__ {int startIndex; scalar_t__ length; } ;
struct TYPE_12__ {int /*<<< orphan*/  bits; TYPE_2__ src; } ;
struct TYPE_14__ {int length; scalar_t__ sense; TYPE_3__ u; scalar_t__ converted; } ;
struct TYPE_13__ {TYPE_1__* regexp; scalar_t__ ok; int /*<<< orphan*/  cx; } ;
struct TYPE_10__ {int source_len; char* source; int flags; } ;
typedef  TYPE_4__ REGlobalData ;
typedef  TYPE_5__ RECharSet ;
typedef  int INT ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  AddCharacterRangeToCharSet (TYPE_5__*,char,char) ; 
 int /*<<< orphan*/  AddCharacterToCharSet (TYPE_5__*,char) ; 
 scalar_t__ FALSE ; 
 int JS7_UNDEC (char) ; 
 int /*<<< orphan*/  JS_ISWORD (char const) ; 
 int /*<<< orphan*/  JS_ReportOutOfMemory (int /*<<< orphan*/ ) ; 
 int REG_FOLD ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  heap_alloc (int) ; 
 int /*<<< orphan*/  isASCIIHexDigit (char,int*) ; 
 int /*<<< orphan*/  iswspace (int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 char towlower (char) ; 
 char towupper (char) ; 

__attribute__((used)) static BOOL
ProcessCharSet(REGlobalData *gData, RECharSet *charSet)
{
    const WCHAR *src, *end;
    BOOL inRange = FALSE;
    WCHAR rangeStart = 0;
    UINT byteLength, n;
    WCHAR c, thisCh;
    INT nDigits, i;

    assert(!charSet->converted);
    /*
     * Assert that startIndex and length points to chars inside [] inside
     * source string.
     */
    assert(1 <= charSet->u.src.startIndex);
    assert(charSet->u.src.startIndex < gData->regexp->source_len);
    assert(charSet->u.src.length <= gData->regexp->source_len
            - 1 - charSet->u.src.startIndex);

    charSet->converted = TRUE;
    src = gData->regexp->source + charSet->u.src.startIndex;

    end = src + charSet->u.src.length;

    assert(src[-1] == '[' && end[0] == ']');

    byteLength = (charSet->length >> 3) + 1;
    charSet->u.bits = heap_alloc(byteLength);
    if (!charSet->u.bits) {
        JS_ReportOutOfMemory(gData->cx);
        gData->ok = FALSE;
        return FALSE;
    }
    memset(charSet->u.bits, 0, byteLength);

    if (src == end)
        return TRUE;

    if (*src == '^') {
        assert(charSet->sense == FALSE);
        ++src;
    } else {
        assert(charSet->sense == TRUE);
    }

    while (src != end) {
        switch (*src) {
          case '\\':
            ++src;
            c = *src++;
            switch (c) {
              case 'b':
                thisCh = 0x8;
                break;
              case 'f':
                thisCh = 0xC;
                break;
              case 'n':
                thisCh = 0xA;
                break;
              case 'r':
                thisCh = 0xD;
                break;
              case 't':
                thisCh = 0x9;
                break;
              case 'v':
                thisCh = 0xB;
                break;
              case 'c':
                if (src < end && JS_ISWORD(*src)) {
                    thisCh = (WCHAR)(*src++ & 0x1F);
                } else {
                    --src;
                    thisCh = '\\';
                }
                break;
              case 'x':
                nDigits = 2;
                goto lexHex;
              case 'u':
                nDigits = 4;
            lexHex:
                n = 0;
                for (i = 0; (i < nDigits) && (src < end); i++) {
                    UINT digit;
                    c = *src++;
                    if (!isASCIIHexDigit(c, &digit)) {
                        /*
                         * Back off to accepting the original '\'
                         * as a literal
                         */
                        src -= i + 1;
                        n = '\\';
                        break;
                    }
                    n = (n << 4) | digit;
                }
                thisCh = (WCHAR)n;
                break;
              case '0':
              case '1':
              case '2':
              case '3':
              case '4':
              case '5':
              case '6':
              case '7':
                /*
                 *  This is a non-ECMA extension - decimal escapes (in this
                 *  case, octal!) are supposed to be an error inside class
                 *  ranges, but supported here for backwards compatibility.
                 */
                n = JS7_UNDEC(c);
                c = *src;
                if ('0' <= c && c <= '7') {
                    src++;
                    n = 8 * n + JS7_UNDEC(c);
                    c = *src;
                    if ('0' <= c && c <= '7') {
                        src++;
                        i = 8 * n + JS7_UNDEC(c);
                        if (i <= 0377)
                            n = i;
                        else
                            src--;
                    }
                }
                thisCh = (WCHAR)n;
                break;

              case 'd':
                AddCharacterRangeToCharSet(charSet, '0', '9');
                continue;   /* don't need range processing */
              case 'D':
                AddCharacterRangeToCharSet(charSet, 0, '0' - 1);
                AddCharacterRangeToCharSet(charSet,
                                           (WCHAR)('9' + 1),
                                           (WCHAR)charSet->length);
                continue;
              case 's':
                for (i = (INT)charSet->length; i >= 0; i--)
                    if (iswspace(i))
                        AddCharacterToCharSet(charSet, (WCHAR)i);
                continue;
              case 'S':
                for (i = (INT)charSet->length; i >= 0; i--)
                    if (!iswspace(i))
                        AddCharacterToCharSet(charSet, (WCHAR)i);
                continue;
              case 'w':
                for (i = (INT)charSet->length; i >= 0; i--)
                    if (JS_ISWORD(i))
                        AddCharacterToCharSet(charSet, (WCHAR)i);
                continue;
              case 'W':
                for (i = (INT)charSet->length; i >= 0; i--)
                    if (!JS_ISWORD(i))
                        AddCharacterToCharSet(charSet, (WCHAR)i);
                continue;
              default:
                thisCh = c;
                break;

            }
            break;

          default:
            thisCh = *src++;
            break;

        }
        if (inRange) {
            if (gData->regexp->flags & REG_FOLD) {
                assert(rangeStart <= thisCh);
                for (i = rangeStart; i <= thisCh; i++) {
                    WCHAR uch, dch;

                    AddCharacterToCharSet(charSet, i);
                    uch = towupper(i);
                    dch = towlower(i);
                    if (i != uch)
                        AddCharacterToCharSet(charSet, uch);
                    if (i != dch)
                        AddCharacterToCharSet(charSet, dch);
                }
            } else {
                AddCharacterRangeToCharSet(charSet, rangeStart, thisCh);
            }
            inRange = FALSE;
        } else {
            if (gData->regexp->flags & REG_FOLD) {
                AddCharacterToCharSet(charSet, towupper(thisCh));
                AddCharacterToCharSet(charSet, towlower(thisCh));
            } else {
                AddCharacterToCharSet(charSet, thisCh);
            }
            if (src < end - 1) {
                if (*src == '-') {
                    ++src;
                    inRange = TRUE;
                    rangeStart = thisCh;
                }
            }
        }
    }
    return TRUE;
}