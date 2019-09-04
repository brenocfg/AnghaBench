#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct RtfData {int char_pos; int force_color; TYPE_3__* current_link; int /*<<< orphan*/  font_scale; } ;
typedef  scalar_t__ UINT ;
struct TYPE_17__ {char const* lpszPath; TYPE_4__* windows; int /*<<< orphan*/  numWindows; TYPE_2__* fonts; scalar_t__ hasPhrases40; scalar_t__ hasPhrases; } ;
struct TYPE_16__ {TYPE_6__* file; } ;
struct TYPE_15__ {int /*<<< orphan*/  name; } ;
struct TYPE_14__ {scalar_t__ cookie; int cpMax; } ;
struct TYPE_12__ {unsigned int lfHeight; int lfWeight; int /*<<< orphan*/  lfItalic; int /*<<< orphan*/  lfStrikeOut; int /*<<< orphan*/  lfUnderline; } ;
struct TYPE_13__ {TYPE_1__ LogFont; } ;
typedef  int /*<<< orphan*/  SIZE_T ;
typedef  scalar_t__ LONG ;
typedef  TYPE_5__ HLPFILE_PAGE ;
typedef  scalar_t__ BYTE ;
typedef  int BOOL ;

/* Variables and functions */
 int FALSE ; 
 short GET_SHORT (scalar_t__ const*,int) ; 
 scalar_t__ const GET_UINT (scalar_t__ const*,int) ; 
 int GET_USHORT (scalar_t__ const*,int) ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/  HLPFILE_AllocLink (struct RtfData*,scalar_t__,char const*,int,scalar_t__ const,int,int,int) ; 
 int HLPFILE_HalfPointsScale (TYPE_5__*,unsigned int) ; 
 int /*<<< orphan*/  HLPFILE_RtfAddControl (struct RtfData*,char*) ; 
 int /*<<< orphan*/  HLPFILE_RtfAddGfxByAddr (struct RtfData*,TYPE_6__*,scalar_t__ const*,scalar_t__) ; 
 int /*<<< orphan*/  HLPFILE_RtfAddGfxByIndex (struct RtfData*,TYPE_6__*,short) ; 
 int /*<<< orphan*/  HLPFILE_RtfAddText (struct RtfData*,char*) ; 
 int /*<<< orphan*/  HLPFILE_Uncompress2 (TYPE_6__*,scalar_t__*,scalar_t__*,scalar_t__*,scalar_t__*) ; 
 int /*<<< orphan*/  HLPFILE_Uncompress3 (TYPE_6__*,char*,char*,scalar_t__*,scalar_t__*) ; 
 scalar_t__ HLP_DISPLAY ; 
 scalar_t__ HLP_DISPLAY30 ; 
 scalar_t__ HLP_TABLE ; 
 char* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int MulDiv (int,short,int) ; 
 int TRUE ; 
 int /*<<< orphan*/  WINE_FIXME (char*,...) ; 
 int /*<<< orphan*/  WINE_TRACE (char*,scalar_t__ const,...) ; 
 int /*<<< orphan*/  WINE_WARN (char*,...) ; 
 scalar_t__ const debugstr_a (char const*) ; 
 scalar_t__ fetch_long (scalar_t__ const**) ; 
 unsigned int fetch_short (scalar_t__ const**) ; 
 unsigned int fetch_ushort (scalar_t__ const**) ; 
 scalar_t__ hlp_link_link ; 
 scalar_t__ hlp_link_macro ; 
 scalar_t__ hlp_link_popup ; 
 int /*<<< orphan*/  memcpy (char*,scalar_t__*,scalar_t__) ; 
 int /*<<< orphan*/  sprintf (char*,char*,...) ; 
 int /*<<< orphan*/  strcmp (char const*,int /*<<< orphan*/ ) ; 
 scalar_t__ strlen (char const*) ; 

__attribute__((used)) static BOOL HLPFILE_BrowseParagraph(HLPFILE_PAGE* page, struct RtfData* rd,
                                    BYTE *buf, BYTE* end, unsigned* parlen)
{
    UINT               textsize;
    const BYTE        *format, *format_end;
    char              *text, *text_base, *text_end;
    LONG               size, blocksize, datalen;
    unsigned short     bits;
    unsigned           ncol = 1;
    short              nc, lastcol, table_width;
    char               tmp[256];
    BOOL               ret = FALSE;

    if (buf + 0x19 > end) {WINE_WARN("header too small\n"); return FALSE;};

    *parlen = 0;
    blocksize = GET_UINT(buf, 0);
    size = GET_UINT(buf, 0x4);
    datalen = GET_UINT(buf, 0x10);
    text = text_base = HeapAlloc(GetProcessHeap(), 0, size);
    if (!text) return FALSE;
    if (size > blocksize - datalen)
    {
        /* need to decompress */
        if (page->file->hasPhrases)
            HLPFILE_Uncompress2(page->file, buf + datalen, end, (BYTE*)text, (BYTE*)text + size);
        else if (page->file->hasPhrases40)
            HLPFILE_Uncompress3(page->file, text, text + size, buf + datalen, end);
        else
        {
            WINE_FIXME("Text size is too long, splitting\n");
            size = blocksize - datalen;
            memcpy(text, buf + datalen, size);
        }
    }
    else
        memcpy(text, buf + datalen, size);

    text_end = text + size;

    format = buf + 0x15;
    format_end = buf + GET_UINT(buf, 0x10);

    WINE_TRACE("Record type (buf[0x14]) = 0x%x\n", buf[0x14]);

    if (buf[0x14] == HLP_DISPLAY || buf[0x14] == HLP_TABLE)
    {
        fetch_long(&format);
        *parlen = fetch_ushort(&format);
    }

    if (buf[0x14] == HLP_TABLE)
    {
        unsigned char    type;

        ncol = *format++;

        if (!HLPFILE_RtfAddControl(rd, "\\trowd")) goto done;
        type = *format++;
        if (type == 0 || type == 2)
        {
            table_width = GET_SHORT(format, 0);
            format += 2;
            if (!HLPFILE_RtfAddControl(rd, "\\trqc")) goto done;
        }
        else
            table_width = 32767;
        WINE_TRACE("New table: cols=%d type=%x width=%d\n",
                   ncol, type, table_width);
        if (ncol > 1)
        {
            int     pos;
            sprintf(tmp, "\\trgaph%d\\trleft%d",
                    MulDiv(HLPFILE_HalfPointsScale(page, GET_SHORT(format, 6)), table_width, 32767),
                    MulDiv(HLPFILE_HalfPointsScale(page, GET_SHORT(format, 2) - GET_SHORT(format, 6)), table_width, 32767) - 1);
            if (!HLPFILE_RtfAddControl(rd, tmp)) goto done;
            pos = GET_SHORT(format, 6) / 2;
            for (nc = 0; nc < ncol; nc++)
            {
                WINE_TRACE("column(%d/%d) gap=%d width=%d\n",
                           nc, ncol, GET_SHORT(format, nc*4),
                           GET_SHORT(format, nc*4+2));
                pos += GET_SHORT(format, nc * 4) + GET_SHORT(format, nc * 4 + 2);
                sprintf(tmp, "\\cellx%d",
                        MulDiv(HLPFILE_HalfPointsScale(page, pos), table_width, 32767));
                if (!HLPFILE_RtfAddControl(rd, tmp)) goto done;
            }
        }
        else
        {
            WINE_TRACE("column(0/%d) gap=%d width=%d\n",
                       ncol, GET_SHORT(format, 0), GET_SHORT(format, 2));
            sprintf(tmp, "\\trleft%d\\cellx%d ",
                    MulDiv(HLPFILE_HalfPointsScale(page, GET_SHORT(format, 2)), table_width, 32767) - 1,
                    MulDiv(HLPFILE_HalfPointsScale(page, GET_SHORT(format, 0)), table_width, 32767));
            if (!HLPFILE_RtfAddControl(rd, tmp)) goto done;
        }
        format += ncol * 4;
    }

    lastcol = -1;
    for (nc = 0; nc < ncol; /**/)
    {
        WINE_TRACE("looking for format at offset %lu in column %d\n", (SIZE_T)(format - (buf + 0x15)), nc);
        if (!HLPFILE_RtfAddControl(rd, "\\pard")) goto done;
        if (buf[0x14] == HLP_TABLE)
        {
            nc = lastcol = GET_SHORT(format, 0);
            if (nc == -1) /* last column */
            {
                if (!HLPFILE_RtfAddControl(rd, "\\row")) goto done;
                rd->char_pos += 2;
                break;
            }
            format += 5;
            if (!HLPFILE_RtfAddControl(rd, "\\intbl")) goto done;
        }
        else nc++;
        if (buf[0x14] == HLP_DISPLAY30)
            format += 6;
        else
            format += 4;
        bits = GET_USHORT(format, 0); format += 2;
        if (bits & 0x0001) fetch_long(&format);
        if (bits & 0x0002)
        {
            sprintf(tmp, "\\sb%d", HLPFILE_HalfPointsScale(page, fetch_short(&format)));
            if (!HLPFILE_RtfAddControl(rd, tmp)) goto done;
        }
        if (bits & 0x0004)
        {
            sprintf(tmp, "\\sa%d", HLPFILE_HalfPointsScale(page, fetch_short(&format)));
            if (!HLPFILE_RtfAddControl(rd, tmp)) goto done;
        }
        if (bits & 0x0008)
        {
            sprintf(tmp, "\\sl%d", HLPFILE_HalfPointsScale(page, fetch_short(&format)));
            if (!HLPFILE_RtfAddControl(rd, tmp)) goto done;
        }
        if (bits & 0x0010)
        {
            sprintf(tmp, "\\li%d", HLPFILE_HalfPointsScale(page, fetch_short(&format)));
            if (!HLPFILE_RtfAddControl(rd, tmp)) goto done;
        }
        if (bits & 0x0020)
        {
            sprintf(tmp, "\\ri%d", HLPFILE_HalfPointsScale(page, fetch_short(&format)));
            if (!HLPFILE_RtfAddControl(rd, tmp)) goto done;
        }
        if (bits & 0x0040)
        {
            sprintf(tmp, "\\fi%d", HLPFILE_HalfPointsScale(page, fetch_short(&format)));
            if (!HLPFILE_RtfAddControl(rd, tmp)) goto done;
        }
        if (bits & 0x0100)
        {
            BYTE        brdr = *format++;
            short       w;

            if ((brdr & 0x01) && !HLPFILE_RtfAddControl(rd, "\\box")) goto done;
            if ((brdr & 0x02) && !HLPFILE_RtfAddControl(rd, "\\brdrt")) goto done;
            if ((brdr & 0x04) && !HLPFILE_RtfAddControl(rd, "\\brdrl")) goto done;
            if ((brdr & 0x08) && !HLPFILE_RtfAddControl(rd, "\\brdrb")) goto done;
            if ((brdr & 0x10) && !HLPFILE_RtfAddControl(rd, "\\brdrr")) goto done;
            if ((brdr & 0x20) && !HLPFILE_RtfAddControl(rd, "\\brdrth")) goto done;
            if (!(brdr & 0x20) && !HLPFILE_RtfAddControl(rd, "\\brdrs")) goto done;
            if ((brdr & 0x40) && !HLPFILE_RtfAddControl(rd, "\\brdrdb")) goto done;
            /* 0x80: unknown */

            w = GET_SHORT(format, 0); format += 2;
            if (w)
            {
                sprintf(tmp, "\\brdrw%d", HLPFILE_HalfPointsScale(page, w));
                if (!HLPFILE_RtfAddControl(rd, tmp)) goto done;
            }
        }
        if (bits & 0x0200)
        {
            int                 i, ntab = fetch_short(&format);
            unsigned            tab, ts;
            const char*         kind;

            for (i = 0; i < ntab; i++)
            {
                tab = fetch_ushort(&format);
                ts = (tab & 0x4000) ? fetch_ushort(&format) : 0 /* left */;
                switch (ts)
                {
                default: WINE_FIXME("Unknown tab style %x\n", ts);
                /* fall through */
                case 0: kind = ""; break;
                case 1: kind = "\\tqr"; break;
                case 2: kind = "\\tqc"; break;
                }
                /* FIXME: do kind */
                sprintf(tmp, "%s\\tx%d",
                        kind, HLPFILE_HalfPointsScale(page, tab & 0x3FFF));
                if (!HLPFILE_RtfAddControl(rd, tmp)) goto done;
            }
        }
        switch (bits & 0xc00)
        {
        default: WINE_FIXME("Unsupported alignment 0xC00\n"); break;
        case 0: if (!HLPFILE_RtfAddControl(rd, "\\ql")) goto done; break;
        case 0x400: if (!HLPFILE_RtfAddControl(rd, "\\qr")) goto done; break;
        case 0x800: if (!HLPFILE_RtfAddControl(rd, "\\qc")) goto done; break;
        }

        /* 0x1000 doesn't need space */
        if ((bits & 0x1000) && !HLPFILE_RtfAddControl(rd, "\\keep")) goto done;
        if ((bits & 0xE080) != 0) 
            WINE_FIXME("Unsupported bits %04x, potential trouble ahead\n", bits);

        while (text < text_end && format < format_end)
        {
            WINE_TRACE("Got text: %s (%p/%p - %p/%p)\n", debugstr_a(text), text, text_end, format, format_end);
            textsize = strlen(text);
            if (textsize)
            {
                if (rd->force_color)
                {
                    if ((rd->current_link->cookie == hlp_link_popup) ?
                        !HLPFILE_RtfAddControl(rd, "{\\uld\\cf1") :
                        !HLPFILE_RtfAddControl(rd, "{\\ul\\cf1")) goto done;
                }
                if (!HLPFILE_RtfAddText(rd, text)) goto done;
                if (rd->force_color && !HLPFILE_RtfAddControl(rd, "}")) goto done;
                rd->char_pos += textsize;
            }
            /* else: null text, keep on storing attributes */
            text += textsize + 1;

            WINE_TRACE("format=0x%02x\n", *format);
	    if (*format == 0xff)
            {
                format++;
                break;
            }

            switch (*format)
            {
            case 0x20:
                WINE_FIXME("NIY20\n");
                format += 5;
                break;

            case 0x21:
                WINE_FIXME("NIY21\n");
                format += 3;
                break;

	    case 0x80:
                {
                    unsigned    font = GET_USHORT(format, 1);
                    unsigned    fs;

                    WINE_TRACE("Changing font to %d\n", font);
                    format += 3;
                    /* Font size in hlpfile is given in the same units as
                       rtf control word \fs uses (half-points). */
                    switch (rd->font_scale)
                    {
                    case 0: fs = page->file->fonts[font].LogFont.lfHeight - 4; break;
                    default:
                    case 1: fs = page->file->fonts[font].LogFont.lfHeight; break;
                    case 2: fs = page->file->fonts[font].LogFont.lfHeight + 4; break;
                    }
                    /* FIXME: colors are missing, at a minimum; also, the bold attribute loses information */

                    sprintf(tmp, "\\f%u\\cf%u\\fs%u%s%s%s%s",
                            font, font + 2, fs,
                            page->file->fonts[font].LogFont.lfWeight > 400 ? "\\b" : "\\b0",
                            page->file->fonts[font].LogFont.lfItalic ? "\\i" : "\\i0",
                            page->file->fonts[font].LogFont.lfUnderline ? "\\ul" : "\\ul0",
                            page->file->fonts[font].LogFont.lfStrikeOut ? "\\strike" : "\\strike0");
                    if (!HLPFILE_RtfAddControl(rd, tmp)) goto done;
                }
               break;

	    case 0x81:
                if (!HLPFILE_RtfAddControl(rd, "\\line")) goto done;
                format += 1;
                rd->char_pos++;
                break;

	    case 0x82:
                if (buf[0x14] == HLP_TABLE)
                {
                    if (format[1] != 0xFF)
                    {
                        if (!HLPFILE_RtfAddControl(rd, "\\par\\intbl")) goto done;
                    }
                    else if (GET_SHORT(format, 2) == -1)
                    {
                        if (!HLPFILE_RtfAddControl(rd, "\\cell\\intbl\\row")) goto done;
                        rd->char_pos += 2;
                    }
                    else if (GET_SHORT(format, 2) == lastcol)
                    {
                        if (!HLPFILE_RtfAddControl(rd, "\\par\\pard")) goto done;
                    }
                    else
                    {
                        if (!HLPFILE_RtfAddControl(rd, "\\cell\\pard")) goto done;
                    }
                }
                else if (!HLPFILE_RtfAddControl(rd, "\\par")) goto done;
                format += 1;
                rd->char_pos++;
                break;

	    case 0x83:
                if (!HLPFILE_RtfAddControl(rd, "\\tab")) goto done;
                format += 1;
                rd->char_pos++;
                break;

#if 0
	    case 0x84:
                format += 3;
                break;
#endif

	    case 0x86:
	    case 0x87:
	    case 0x88:
                {
                    BYTE    type = format[1];

                    /* FIXME: we don't use 'BYTE    pos = (*format - 0x86);' for the image position */
                    format += 2;
                    size = fetch_long(&format);

                    switch (type)
                    {
                    case 0x22:
                        fetch_ushort(&format); /* hot spot */
                        /* fall through */
                    case 0x03:
                        switch (GET_SHORT(format, 0))
                        {
                        case 0:
                            HLPFILE_RtfAddGfxByIndex(rd, page->file, GET_SHORT(format, 2));
                            rd->char_pos++;
                            break;
                        case 1:
                            WINE_FIXME("does it work ??? %x<%u>#%u\n",
                                       GET_SHORT(format, 0),
                                       size, GET_SHORT(format, 2));
                            HLPFILE_RtfAddGfxByAddr(rd, page->file, format + 2, size - 4);
                            rd->char_pos++;
                           break;
                        default:
                            WINE_FIXME("??? %u\n", GET_SHORT(format, 0));
                            break;
                        }
                        break;
                    case 0x05:
                        WINE_FIXME("Got an embedded element %s\n", debugstr_a((char *)format + 6));
                        break;
                    default:
                        WINE_FIXME("Got a type %d picture\n", type);
                        break;
                    }
                    format += size;
                }
                break;

	    case 0x89:
                format += 1;
                if (!rd->current_link)
                    WINE_FIXME("No existing link\n");
                rd->current_link->cpMax = rd->char_pos;
                rd->current_link = NULL;
                rd->force_color = FALSE;
                break;

            case 0x8B:
                if (!HLPFILE_RtfAddControl(rd, "\\~")) goto done;
                format += 1;
                rd->char_pos++;
                break;

            case 0x8C:
                if (!HLPFILE_RtfAddControl(rd, "\\_")) goto done;
                /* FIXME: it could be that hyphen is also in input stream !! */
                format += 1;
                rd->char_pos++;
                break;

#if 0
	    case 0xA9:
                format += 2;
                break;
#endif

            case 0xC8:
            case 0xCC:
                WINE_TRACE("macro => %s\n", debugstr_a((char *)format + 3));
                HLPFILE_AllocLink(rd, hlp_link_macro, (const char*)format + 3,
                                  GET_USHORT(format, 1), 0, !(*format & 4), FALSE, -1);
                format += 3 + GET_USHORT(format, 1);
                break;

            case 0xE0:
            case 0xE1:
                WINE_WARN("jump topic 1 => %u\n", GET_UINT(format, 1));
                HLPFILE_AllocLink(rd, (*format & 1) ? hlp_link_link : hlp_link_popup,
                                  page->file->lpszPath, -1, GET_UINT(format, 1), TRUE, FALSE, -1);


                format += 5;
                break;

	    case 0xE2:
	    case 0xE3:
            case 0xE6:
            case 0xE7:
                WINE_WARN("jump topic 1 => %u\n", GET_UINT(format, 1));
                HLPFILE_AllocLink(rd, (*format & 1) ? hlp_link_link : hlp_link_popup,
                                  page->file->lpszPath, -1, GET_UINT(format, 1),
                                  !(*format & 4), FALSE, -1);
                format += 5;
                break;

	    case 0xEA:
            case 0xEB:
            case 0xEE:
            case 0xEF:
                {
                    const char*       ptr = (const char*) format + 8;
                    BYTE        type = format[3];
                    int         wnd = -1;

                    switch (type)
                    {
                    case 1:
                        wnd = *ptr;
                        /* fall through */
                    case 0:
                        ptr = page->file->lpszPath;
                        break;
                    case 6:
                        for (wnd = page->file->numWindows - 1; wnd >= 0; wnd--)
                        {
                            if (!strcmp(ptr, page->file->windows[wnd].name)) break;
                        }
                        if (wnd == -1)
                            WINE_WARN("Couldn't find window info for %s\n", debugstr_a(ptr));
                        ptr += strlen(ptr) + 1;
                        /* fall through */
                    case 4:
                        break;
                    default:
                        WINE_WARN("Unknown link type %d\n", type);
                        break;
                    }
                    HLPFILE_AllocLink(rd, (*format & 1) ? hlp_link_link : hlp_link_popup,
                                      ptr, -1, GET_UINT(format, 4), !(*format & 4), FALSE, wnd);
                }
                format += 3 + GET_USHORT(format, 1);
                break;

	    default:
                WINE_WARN("format %02x\n", *format);
                format++;
	    }
	}
    }
    ret = TRUE;
done:

    HeapFree(GetProcessHeap(), 0, text_base);
    return ret;
}