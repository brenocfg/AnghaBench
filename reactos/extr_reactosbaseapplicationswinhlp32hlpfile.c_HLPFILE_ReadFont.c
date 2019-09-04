#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int lfHeight; int lfWeight; int lfItalic; int lfUnderline; int lfStrikeOut; char* lfFaceName; int /*<<< orphan*/  lfPitchAndFamily; int /*<<< orphan*/  lfQuality; int /*<<< orphan*/  lfClipPrecision; int /*<<< orphan*/  lfOutPrecision; int /*<<< orphan*/  lfCharSet; scalar_t__ lfOrientation; scalar_t__ lfEscapement; scalar_t__ lfWidth; } ;
struct TYPE_8__ {TYPE_1__ LogFont; int /*<<< orphan*/  color; scalar_t__ hFont; } ;
struct TYPE_7__ {unsigned int numFonts; int scale; int rounderr; TYPE_3__* fonts; int /*<<< orphan*/  charset; } ;
typedef  int /*<<< orphan*/  HLPFILE_FONT ;
typedef  TYPE_2__ HLPFILE ;
typedef  int BYTE ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  CLIP_DEFAULT_PRECIS ; 
 int /*<<< orphan*/  DEFAULT_PITCH ; 
 int /*<<< orphan*/  DEFAULT_QUALITY ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  FF_DECORATIVE ; 
 int /*<<< orphan*/  FF_MODERN ; 
 int /*<<< orphan*/  FF_ROMAN ; 
 int /*<<< orphan*/  FF_SCRIPT ; 
 int /*<<< orphan*/  FF_SWISS ; 
 int GET_UINT (int*,unsigned int) ; 
 unsigned int GET_USHORT (int*,unsigned int) ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/  HLPFILE_FindSubFile (TYPE_2__*,char*,int**,int**) ; 
 TYPE_3__* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ LF_FACESIZE ; 
 int /*<<< orphan*/  OUT_DEFAULT_PRECIS ; 
 int /*<<< orphan*/  RGB (int,int,int) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  WINE_FIXME (char*,...) ; 
 int /*<<< orphan*/  WINE_TRACE (char*,unsigned int,int,...) ; 
 int /*<<< orphan*/  WINE_WARN (char*) ; 
 int /*<<< orphan*/  debugstr_a (char*) ; 
 int /*<<< orphan*/  memcpy (char*,int*,size_t) ; 
 size_t min (unsigned int,scalar_t__) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 

__attribute__((used)) static BOOL HLPFILE_ReadFont(HLPFILE* hlpfile)
{
    BYTE        *ref, *end;
    unsigned    i, len, idx;
    unsigned    face_num, dscr_num, face_offset, dscr_offset;
    BYTE        flag, family;

    if (!HLPFILE_FindSubFile(hlpfile, "|FONT", &ref, &end))
    {
        WINE_WARN("no subfile FONT\n");
        hlpfile->numFonts = 0;
        hlpfile->fonts = NULL;
        return FALSE;
    }

    ref += 9;

    face_num    = GET_USHORT(ref, 0);
    dscr_num    = GET_USHORT(ref, 2);
    face_offset = GET_USHORT(ref, 4);
    dscr_offset = GET_USHORT(ref, 6);

    WINE_TRACE("Got NumFacenames=%u@%u NumDesc=%u@%u\n",
               face_num, face_offset, dscr_num, dscr_offset);

    hlpfile->numFonts = dscr_num;
    hlpfile->fonts = HeapAlloc(GetProcessHeap(), 0, sizeof(HLPFILE_FONT) * dscr_num);

    len = (dscr_offset - face_offset) / face_num;

    /* mvb font */
    if (face_offset >= 16)
    {
        hlpfile->scale = 1;
        hlpfile->rounderr = 0;
        WINE_FIXME("mvb font: not implemented\n");
        return FALSE;
    }
    /* new font */
    if (face_offset >= 12)
    {
        hlpfile->scale = 1;
        hlpfile->rounderr = 0;
        WINE_FIXME("new font: not implemented\n");
        return FALSE;
    }
    /* old font */
    hlpfile->scale = 10;
    hlpfile->rounderr = 5;
/* EPP     for (i = face_offset; i < dscr_offset; i += len) */
/* EPP         WINE_FIXME("[%d]: %*s\n", i / len, len, ref + i); */
    for (i = 0; i < dscr_num; i++)
    {
        flag = ref[dscr_offset + i * 11 + 0];
        family = ref[dscr_offset + i * 11 + 2];

        hlpfile->fonts[i].LogFont.lfHeight = ref[dscr_offset + i * 11 + 1];
        hlpfile->fonts[i].LogFont.lfWidth = 0;
        hlpfile->fonts[i].LogFont.lfEscapement = 0;
        hlpfile->fonts[i].LogFont.lfOrientation = 0;
        hlpfile->fonts[i].LogFont.lfWeight = (flag & 1) ? 700 : 400;
        hlpfile->fonts[i].LogFont.lfItalic = (flag & 2) != 0;
        hlpfile->fonts[i].LogFont.lfUnderline = (flag & 4) != 0;
        hlpfile->fonts[i].LogFont.lfStrikeOut = (flag & 8) != 0;
        hlpfile->fonts[i].LogFont.lfCharSet = hlpfile->charset;
        hlpfile->fonts[i].LogFont.lfOutPrecision = OUT_DEFAULT_PRECIS;
        hlpfile->fonts[i].LogFont.lfClipPrecision = CLIP_DEFAULT_PRECIS;
        hlpfile->fonts[i].LogFont.lfQuality = DEFAULT_QUALITY;
        hlpfile->fonts[i].LogFont.lfPitchAndFamily = DEFAULT_PITCH;

        switch (family)
        {
        case 0x01: hlpfile->fonts[i].LogFont.lfPitchAndFamily |= FF_MODERN;     break;
        case 0x02: hlpfile->fonts[i].LogFont.lfPitchAndFamily |= FF_ROMAN;      break;
        case 0x03: hlpfile->fonts[i].LogFont.lfPitchAndFamily |= FF_SWISS;      break;
        case 0x04: hlpfile->fonts[i].LogFont.lfPitchAndFamily |= FF_SCRIPT;     break;
        case 0x05: hlpfile->fonts[i].LogFont.lfPitchAndFamily |= FF_DECORATIVE; break;
        default: WINE_FIXME("Unknown family %u\n", family);
        }
        idx = GET_USHORT(ref, dscr_offset + i * 11 + 3);

        if (idx < face_num)
        {
            memcpy(hlpfile->fonts[i].LogFont.lfFaceName, ref + face_offset + idx * len, min(len, LF_FACESIZE - 1));
            hlpfile->fonts[i].LogFont.lfFaceName[min(len, LF_FACESIZE - 1)] = '\0';
        }
        else
        {
            WINE_FIXME("Too high face ref (%u/%u)\n", idx, face_num);
            strcpy(hlpfile->fonts[i].LogFont.lfFaceName, "Helv");
        }
        hlpfile->fonts[i].hFont = 0;
        hlpfile->fonts[i].color = RGB(ref[dscr_offset + i * 11 + 5],
                                      ref[dscr_offset + i * 11 + 6],
                                      ref[dscr_offset + i * 11 + 7]);
#define X(b,s) ((flag & (1 << b)) ? "-"s: "")
        WINE_TRACE("Font[%d]: flags=%02x%s%s%s%s%s%s pSize=%u family=%u face=%s[%u] color=%08x\n",
                   i, flag,
                   X(0, "bold"),
                   X(1, "italic"),
                   X(2, "underline"),
                   X(3, "strikeOut"),
                   X(4, "dblUnderline"),
                   X(5, "smallCaps"),
                   ref[dscr_offset + i * 11 + 1],
                   family,
                   debugstr_a(hlpfile->fonts[i].LogFont.lfFaceName), idx,
                   GET_UINT(ref, dscr_offset + i * 11 + 5) & 0x00FFFFFF);
    }
    return TRUE;
}