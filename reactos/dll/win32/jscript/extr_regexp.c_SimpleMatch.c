#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_5__ ;
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
struct TYPE_17__ {int* cp; } ;
typedef  TYPE_3__ match_state_t ;
typedef  int /*<<< orphan*/  jsbytecode ;
typedef  int WCHAR ;
struct TYPE_15__ {int* bits; } ;
struct TYPE_19__ {int converted; int length; TYPE_1__ u; } ;
struct TYPE_18__ {int* cpbegin; int* cpend; TYPE_2__* regexp; scalar_t__ stateStackTop; } ;
struct TYPE_16__ {int flags; size_t parenCount; size_t source_len; int* source; size_t classCount; TYPE_5__* classList; int /*<<< orphan*/ * program; } ;
typedef  size_t REOp ;
typedef  TYPE_4__ REGlobalData ;
typedef  TYPE_5__ RECharSet ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  ARG_LEN ; 
 TYPE_3__* BackrefMatcher (TYPE_4__*,TYPE_3__*,size_t) ; 
 int FALSE ; 
 TYPE_3__* FlatNIMatcher (TYPE_4__*,TYPE_3__*,int const*,size_t) ; 
 int GET_ARG (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  JS7_ISDEC (int) ; 
 int /*<<< orphan*/  JS_ISWORD (int) ; 
 int REG_MULTILINE ; 
#define  REOP_ALNUM 148 
#define  REOP_BACKREF 147 
#define  REOP_BOL 146 
#define  REOP_CLASS 145 
#define  REOP_DIGIT 144 
#define  REOP_DOT 143 
#define  REOP_EMPTY 142 
#define  REOP_EOL 141 
#define  REOP_FLAT 140 
#define  REOP_FLAT1 139 
#define  REOP_FLAT1i 138 
#define  REOP_FLATi 137 
#define  REOP_NCLASS 136 
#define  REOP_NONALNUM 135 
#define  REOP_NONDIGIT 134 
#define  REOP_NONSPACE 133 
#define  REOP_SPACE 132 
#define  REOP_UCFLAT1 131 
#define  REOP_UCFLAT1i 130 
#define  REOP_WBDRY 129 
#define  REOP_WNONBDRY 128 
 int /*<<< orphan*/  RE_IS_LINE_TERM (int) ; 
 int /*<<< orphan*/ * ReadCompactIndex (int /*<<< orphan*/ *,size_t*) ; 
 int /*<<< orphan*/  TRACE (char*,...) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  debugstr_wn (int const*,size_t) ; 
 int /*<<< orphan*/  iswspace (int) ; 
 char** reop_names ; 
 int /*<<< orphan*/  towupper (int) ; 

__attribute__((used)) static inline match_state_t *
SimpleMatch(REGlobalData *gData, match_state_t *x, REOp op,
            jsbytecode **startpc, BOOL updatecp)
{
    match_state_t *result = NULL;
    WCHAR matchCh;
    size_t parenIndex;
    size_t offset, length, index;
    jsbytecode *pc = *startpc;  /* pc has already been incremented past op */
    const WCHAR *source;
    const WCHAR *startcp = x->cp;
    WCHAR ch;
    RECharSet *charSet;

    const char *opname = reop_names[op];
    TRACE("\n%06d: %*s%s\n", (int)(pc - gData->regexp->program),
          (int)gData->stateStackTop * 2, "", opname);

    switch (op) {
      case REOP_EMPTY:
        result = x;
        break;
      case REOP_BOL:
        if (x->cp != gData->cpbegin) {
            if (/*!gData->cx->regExpStatics.multiline &&  FIXME !!! */
                !(gData->regexp->flags & REG_MULTILINE)) {
                break;
            }
            if (!RE_IS_LINE_TERM(x->cp[-1]))
                break;
        }
        result = x;
        break;
      case REOP_EOL:
        if (x->cp != gData->cpend) {
            if (/*!gData->cx->regExpStatics.multiline &&*/
                !(gData->regexp->flags & REG_MULTILINE)) {
                break;
            }
            if (!RE_IS_LINE_TERM(*x->cp))
                break;
        }
        result = x;
        break;
      case REOP_WBDRY:
        if ((x->cp == gData->cpbegin || !JS_ISWORD(x->cp[-1])) ^
            !(x->cp != gData->cpend && JS_ISWORD(*x->cp))) {
            result = x;
        }
        break;
      case REOP_WNONBDRY:
        if ((x->cp == gData->cpbegin || !JS_ISWORD(x->cp[-1])) ^
            (x->cp != gData->cpend && JS_ISWORD(*x->cp))) {
            result = x;
        }
        break;
      case REOP_DOT:
        if (x->cp != gData->cpend && !RE_IS_LINE_TERM(*x->cp)) {
            result = x;
            result->cp++;
        }
        break;
      case REOP_DIGIT:
        if (x->cp != gData->cpend && JS7_ISDEC(*x->cp)) {
            result = x;
            result->cp++;
        }
        break;
      case REOP_NONDIGIT:
        if (x->cp != gData->cpend && !JS7_ISDEC(*x->cp)) {
            result = x;
            result->cp++;
        }
        break;
      case REOP_ALNUM:
        if (x->cp != gData->cpend && JS_ISWORD(*x->cp)) {
            result = x;
            result->cp++;
        }
        break;
      case REOP_NONALNUM:
        if (x->cp != gData->cpend && !JS_ISWORD(*x->cp)) {
            result = x;
            result->cp++;
        }
        break;
      case REOP_SPACE:
        if (x->cp != gData->cpend && iswspace(*x->cp)) {
            result = x;
            result->cp++;
        }
        break;
      case REOP_NONSPACE:
        if (x->cp != gData->cpend && !iswspace(*x->cp)) {
            result = x;
            result->cp++;
        }
        break;
      case REOP_BACKREF:
        pc = ReadCompactIndex(pc, &parenIndex);
        assert(parenIndex < gData->regexp->parenCount);
        result = BackrefMatcher(gData, x, parenIndex);
        break;
      case REOP_FLAT:
        pc = ReadCompactIndex(pc, &offset);
        assert(offset < gData->regexp->source_len);
        pc = ReadCompactIndex(pc, &length);
        assert(1 <= length);
        assert(length <= gData->regexp->source_len - offset);
        if (length <= (size_t)(gData->cpend - x->cp)) {
            source = gData->regexp->source + offset;
            TRACE("%s\n", debugstr_wn(source, length));
            for (index = 0; index != length; index++) {
                if (source[index] != x->cp[index])
                    return NULL;
            }
            x->cp += length;
            result = x;
        }
        break;
      case REOP_FLAT1:
        matchCh = *pc++;
        TRACE(" '%c' == '%c'\n", (char)matchCh, (char)*x->cp);
        if (x->cp != gData->cpend && *x->cp == matchCh) {
            result = x;
            result->cp++;
        }
        break;
      case REOP_FLATi:
        pc = ReadCompactIndex(pc, &offset);
        assert(offset < gData->regexp->source_len);
        pc = ReadCompactIndex(pc, &length);
        assert(1 <= length);
        assert(length <= gData->regexp->source_len - offset);
        source = gData->regexp->source;
        result = FlatNIMatcher(gData, x, source + offset, length);
        break;
      case REOP_FLAT1i:
        matchCh = *pc++;
        if (x->cp != gData->cpend && towupper(*x->cp) == towupper(matchCh)) {
            result = x;
            result->cp++;
        }
        break;
      case REOP_UCFLAT1:
        matchCh = GET_ARG(pc);
        TRACE(" '%c' == '%c'\n", (char)matchCh, (char)*x->cp);
        pc += ARG_LEN;
        if (x->cp != gData->cpend && *x->cp == matchCh) {
            result = x;
            result->cp++;
        }
        break;
      case REOP_UCFLAT1i:
        matchCh = GET_ARG(pc);
        pc += ARG_LEN;
        if (x->cp != gData->cpend && towupper(*x->cp) == towupper(matchCh)) {
            result = x;
            result->cp++;
        }
        break;
      case REOP_CLASS:
        pc = ReadCompactIndex(pc, &index);
        assert(index < gData->regexp->classCount);
        if (x->cp != gData->cpend) {
            charSet = &gData->regexp->classList[index];
            assert(charSet->converted);
            ch = *x->cp;
            index = ch >> 3;
            if (charSet->length != 0 &&
                ch <= charSet->length &&
                (charSet->u.bits[index] & (1 << (ch & 0x7)))) {
                result = x;
                result->cp++;
            }
        }
        break;
      case REOP_NCLASS:
        pc = ReadCompactIndex(pc, &index);
        assert(index < gData->regexp->classCount);
        if (x->cp != gData->cpend) {
            charSet = &gData->regexp->classList[index];
            assert(charSet->converted);
            ch = *x->cp;
            index = ch >> 3;
            if (charSet->length == 0 ||
                ch > charSet->length ||
                !(charSet->u.bits[index] & (1 << (ch & 0x7)))) {
                result = x;
                result->cp++;
            }
        }
        break;

      default:
        assert(FALSE);
    }
    if (result) {
        if (!updatecp)
            x->cp = startcp;
        *startpc = pc;
        TRACE(" *\n");
        return result;
    }
    x->cp = startcp;
    return NULL;
}