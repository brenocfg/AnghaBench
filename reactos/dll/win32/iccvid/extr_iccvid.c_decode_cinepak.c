#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  (* fn_cvid_v4 ) (unsigned char*,unsigned char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ;
typedef  int /*<<< orphan*/  (* fn_cvid_v1 ) (unsigned char*,unsigned char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;
typedef  int /*<<< orphan*/  cvid_codebook ;
struct TYPE_3__ {unsigned int strip_num; int /*<<< orphan*/ ** v1_codebook; int /*<<< orphan*/ ** v4_codebook; } ;
typedef  TYPE_1__ cinepak_info ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  ERR (char*,...) ; 
 unsigned long MAX_STRIPS ; 
 int /*<<< orphan*/  TRACE (char*,unsigned long,long,...) ; 
 int /*<<< orphan*/  WARN (char*,int,int,...) ; 
 int /*<<< orphan*/  cvid_v1_15 (unsigned char*,unsigned char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cvid_v1_16 (unsigned char*,unsigned char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cvid_v1_24 (unsigned char*,unsigned char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cvid_v1_32 (unsigned char*,unsigned char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cvid_v4_15 (unsigned char*,unsigned char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cvid_v4_16 (unsigned char*,unsigned char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cvid_v4_24 (unsigned char*,unsigned char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cvid_v4_32 (unsigned char*,unsigned char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 unsigned int get_addr (int /*<<< orphan*/ ,unsigned long,unsigned long,int,int,unsigned int) ; 
 long get_byte () ; 
 unsigned long get_long () ; 
 int get_stride (unsigned int,int) ; 
 void* get_word () ; 
 void* heap_alloc (int) ; 
 unsigned char* in_buffer ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  read_codebook (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  skip_byte () ; 

__attribute__((used)) static void decode_cinepak(cinepak_info *cvinfo, unsigned char *buf, int size,
           unsigned char *output, unsigned int out_width, unsigned int out_height, int bit_per_pixel, BOOL inverted)
{
    cvid_codebook *v4_codebook, *v1_codebook, *codebook = NULL;
    unsigned long x, y, y_bottom, cnum, strip_id, chunk_id,
                  x0, y0, x1, y1, ci, flag, mask;
    long top_size, chunk_size;
    unsigned char *frm_ptr;
    unsigned int i, cur_strip, addr;
    int d0, d1, d2, d3, frm_stride, bpp = 3;
    fn_cvid_v1 cvid_v1 = cvid_v1_24;
    fn_cvid_v4 cvid_v4 = cvid_v4_24;
    struct frame_header
    {
      unsigned char flags;
      unsigned long length;
      unsigned short width;
      unsigned short height;
      unsigned short strips;
    } frame;

    y = 0;
    y_bottom = 0;
    in_buffer = buf;

    frame.flags = get_byte();
    frame.length = get_byte() << 16;
    frame.length |= get_byte() << 8;
    frame.length |= get_byte();

    switch(bit_per_pixel)
        {
        case 15:
            bpp = 2;
            cvid_v1 = cvid_v1_15;
            cvid_v4 = cvid_v4_15;
            break;
        case 16:
            bpp = 2;
            cvid_v1 = cvid_v1_16;
            cvid_v4 = cvid_v4_16;
            break;
        case 24:
            bpp = 3;
            cvid_v1 = cvid_v1_24;
            cvid_v4 = cvid_v4_24;
            break;
        case 32:
            bpp = 4;
            cvid_v1 = cvid_v1_32;
            cvid_v4 = cvid_v4_32;
            break;
        }

    frm_stride = get_stride(out_width, bpp * 8);
    frm_ptr = output;

    if(frame.length != size)
        {
        if(frame.length & 0x01) frame.length++; /* AVIs tend to have a size mismatch */
        if(frame.length != size)
            {
            ERR("CVID: corruption %d (QT/AVI) != %ld (CV)\n", size, frame.length);
            /* return; */
            }
        }

    frame.width = get_word();
    frame.height = get_word();
    frame.strips = get_word();

    if(frame.strips > cvinfo->strip_num)
        {
        if(frame.strips >= MAX_STRIPS)
            {
            ERR("CVID: strip overflow (more than %d)\n", MAX_STRIPS);
            return;
            }

        for(i = cvinfo->strip_num; i < frame.strips; i++)
            {
            if((cvinfo->v4_codebook[i] = heap_alloc(sizeof(cvid_codebook) * 260)) == NULL)
                {
                ERR("CVID: codebook v4 alloc err\n");
                return;
                }

            if((cvinfo->v1_codebook[i] = heap_alloc(sizeof(cvid_codebook) * 260)) == NULL)
                {
                ERR("CVID: codebook v1 alloc err\n");
                return;
                }
            }
        }
    cvinfo->strip_num = frame.strips;

    TRACE("CVID: %ux%u, strips %u, length %lu\n",
          frame.width, frame.height, frame.strips, frame.length);

    for(cur_strip = 0; cur_strip < frame.strips; cur_strip++)
        {
        v4_codebook = cvinfo->v4_codebook[cur_strip];
        v1_codebook = cvinfo->v1_codebook[cur_strip];

        if((cur_strip > 0) && (!(frame.flags & 0x01)))
            {
            memcpy(cvinfo->v4_codebook[cur_strip], cvinfo->v4_codebook[cur_strip-1], 260 * sizeof(cvid_codebook));
            memcpy(cvinfo->v1_codebook[cur_strip], cvinfo->v1_codebook[cur_strip-1], 260 * sizeof(cvid_codebook));
            }

        strip_id = get_word();        /* 1000 = key strip, 1100 = iter strip */
        top_size = get_word();
        y0 = get_word();        /* FIXME: most of these are ignored at the moment */
        x0 = get_word();
        y1 = get_word();
        x1 = get_word();

        y_bottom += y1;
        top_size -= 12;
        x = 0;
        if(x1 != out_width)
            WARN("CVID: Warning x1 (%ld) != width (%d)\n", x1, out_width);

        TRACE("   %d) %04lx %04ld <%ld,%ld> <%ld,%ld> yt %ld\n",
              cur_strip, strip_id, top_size, x0, y0, x1, y1, y_bottom);

        while(top_size > 0)
            {
            chunk_id  = get_word();
            chunk_size = get_word();

            TRACE("        %04lx %04ld\n", chunk_id, chunk_size);
            top_size -= chunk_size;
            chunk_size -= 4;

            switch(chunk_id)
                {
                    /* -------------------- Codebook Entries -------------------- */
                case 0x2000:
                case 0x2200:
                    codebook = (chunk_id == 0x2200 ? v1_codebook : v4_codebook);
                    cnum = chunk_size/6;
                    for(i = 0; i < cnum; i++) read_codebook(codebook+i, 0);
                    break;

                case 0x2400:
                case 0x2600:        /* 8 bit per pixel */
                    codebook = (chunk_id == 0x2600 ? v1_codebook : v4_codebook);
                    cnum = chunk_size/4;
                    for(i = 0; i < cnum; i++) read_codebook(codebook+i, 1);
                    break;

                case 0x2100:
                case 0x2300:
                    codebook = (chunk_id == 0x2300 ? v1_codebook : v4_codebook);

                    ci = 0;
                    while(chunk_size > 0)
                        {
                        flag = get_long();
                        chunk_size -= 4;

                        for(i = 0; i < 32; i++)
                            {
                            if(flag & 0x80000000)
                                {
                                chunk_size -= 6;
                                read_codebook(codebook+ci, 0);
                                }

                            ci++;
                            flag <<= 1;
                            }
                        }
                    while(chunk_size > 0) { skip_byte(); chunk_size--; }
                    break;

                case 0x2500:
                case 0x2700:        /* 8 bit per pixel */
                    codebook = (chunk_id == 0x2700 ? v1_codebook : v4_codebook);

                    ci = 0;
                    while(chunk_size > 0)
                        {
                        flag = get_long();
                        chunk_size -= 4;

                        for(i = 0; i < 32; i++)
                            {
                            if(flag & 0x80000000)
                                {
                                chunk_size -= 4;
                                read_codebook(codebook+ci, 1);
                                }

                            ci++;
                            flag <<= 1;
                            }
                        }
                    while(chunk_size > 0) { skip_byte(); chunk_size--; }
                    break;

                    /* -------------------- Frame -------------------- */
                case 0x3000:
                    while((chunk_size > 0) && (y < y_bottom))
                        {
                        flag = get_long();
                        chunk_size -= 4;

                        for(i = 0; i < 32; i++)
                            {
                            if(y >= y_bottom) break;
                            if(flag & 0x80000000)    /* 4 bytes per block */
                                {
                                d0 = get_byte();
                                d1 = get_byte();
                                d2 = get_byte();
                                d3 = get_byte();
                                chunk_size -= 4;

                                addr = get_addr(inverted, x, y, frm_stride, bpp, out_height);
                                cvid_v4(frm_ptr + addr, output, frm_stride, inverted, v4_codebook+d0, v4_codebook+d1, v4_codebook+d2, v4_codebook+d3);
                                }
                            else        /* 1 byte per block */
                                {
                                addr = get_addr(inverted, x, y, frm_stride, bpp, out_height);
                                cvid_v1(frm_ptr + addr, output, frm_stride, inverted, v1_codebook + get_byte());

                                chunk_size--;
                                }

                            x += 4;
                            if(x >= out_width)
                                {
                                x = 0;
                                y += 4;
                                }
                            flag <<= 1;
                            }
                        }
                    while(chunk_size > 0) { skip_byte(); chunk_size--; }
                    break;

                case 0x3100:
                    while((chunk_size > 0) && (y < y_bottom))
                        {
                            /* ---- flag bits: 0 = SKIP, 10 = V1, 11 = V4 ---- */
                        flag = get_long();
                        chunk_size -= 4;
                        mask = 0x80000000;

                        while((mask) && (y < y_bottom))
                            {
                            if(flag & mask)
                                {
                                if(mask == 1)
                                    {
                                    if(chunk_size < 0) break;
                                    flag = get_long();
                                    chunk_size -= 4;
                                    mask = 0x80000000;
                                    }
                                else mask >>= 1;

                                if(flag & mask)        /* V4 */
                                    {
                                    d0 = get_byte();
                                    d1 = get_byte();
                                    d2 = get_byte();
                                    d3 = get_byte();
                                    chunk_size -= 4;

                                    addr = get_addr(inverted, x, y, frm_stride, bpp, out_height);
                                    cvid_v4(frm_ptr + addr, output, frm_stride, inverted, v4_codebook+d0, v4_codebook+d1, v4_codebook+d2, v4_codebook+d3);
                                    }
                                else        /* V1 */
                                    {
                                    chunk_size--;

                                    addr = get_addr(inverted, x, y, frm_stride, bpp, out_height);
                                    cvid_v1(frm_ptr + addr, output, frm_stride, inverted, v1_codebook + get_byte());
                                    }
                                }        /* else SKIP */

                            mask >>= 1;
                            x += 4;
                            if(x >= out_width)
                                {
                                x = 0;
                                y += 4;
                                }
                            }
                        }

                    while(chunk_size > 0) { skip_byte(); chunk_size--; }
                    break;

                case 0x3200:        /* each byte is a V1 codebook */
                    while((chunk_size > 0) && (y < y_bottom))
                        {
                        addr = get_addr(inverted, x, y, frm_stride, bpp, out_height);
                        cvid_v1(frm_ptr + addr, output, frm_stride, inverted, v1_codebook + get_byte());

                        chunk_size--;
                        x += 4;
                        if(x >= out_width)
                            {
                            x = 0;
                            y += 4;
                            }
                        }
                    while(chunk_size > 0) { skip_byte(); chunk_size--; }
                    break;

                default:
                    ERR("CVID: unknown chunk_id %08lx\n", chunk_id);
                    while(chunk_size > 0) { skip_byte(); chunk_size--; }
                    break;
                }
            }
        }

    if(frame.length != size)
        {
        if(frame.length & 0x01) frame.length++; /* AVIs tend to have a size mismatch */
        if(frame.length != size)
            {
            long xlen;
            skip_byte();
            xlen = get_byte() << 16;
            xlen |= get_byte() << 8;
            xlen |= get_byte(); /* Read Len */
            WARN("CVID: END INFO chunk size %d cvid size1 %ld cvid size2 %ld\n",
                  size, frame.length, xlen);
            }
        }
}