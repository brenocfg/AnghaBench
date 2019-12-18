#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int u_char ;
typedef  int /*<<< orphan*/  packet ;
typedef  int ngx_uint_t ;
struct TYPE_8__ {int pid; scalar_t__ pts; scalar_t__ dts; int cc; scalar_t__ sid; scalar_t__ key; } ;
typedef  TYPE_1__ ngx_rtmp_mpegts_frame_t ;
struct TYPE_9__ {int /*<<< orphan*/  log; } ;
typedef  TYPE_2__ ngx_rtmp_mpegts_file_t ;
typedef  int ngx_int_t ;
struct TYPE_10__ {int last; int pos; } ;
typedef  TYPE_3__ ngx_buf_t ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_LOG_DEBUG_CORE ; 
 int NGX_OK ; 
 scalar_t__ NGX_RTMP_HLS_DELAY ; 
 int /*<<< orphan*/  ngx_log_debug6 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,scalar_t__,scalar_t__,scalar_t__,int,size_t) ; 
 int /*<<< orphan*/  ngx_memcpy (int*,int,int) ; 
 int /*<<< orphan*/  ngx_memset (int*,int,int) ; 
 int* ngx_movemem (int*,int*,int) ; 
 int ngx_rtmp_mpegts_write_file (TYPE_2__*,int*,int) ; 
 int* ngx_rtmp_mpegts_write_pcr (int*,scalar_t__) ; 
 int* ngx_rtmp_mpegts_write_pts (int*,int,scalar_t__) ; 

ngx_int_t
ngx_rtmp_mpegts_write_frame(ngx_rtmp_mpegts_file_t *file,
    ngx_rtmp_mpegts_frame_t *f, ngx_buf_t *b)
{
    ngx_uint_t  pes_size, header_size, body_size, in_size, stuff_size, flags;
    u_char      packet[188], *p, *base;
    ngx_int_t   first, rc;

    ngx_log_debug6(NGX_LOG_DEBUG_CORE, file->log, 0,
                   "mpegts: pid=%ui, sid=%ui, pts=%uL, "
                   "dts=%uL, key=%ui, size=%ui",
                   f->pid, f->sid, f->pts, f->dts,
                   (ngx_uint_t) f->key, (size_t) (b->last - b->pos));

    first = 1;

    while (b->pos < b->last) {
        p = packet;

        f->cc++;

        *p++ = 0x47;
        *p++ = (u_char) (f->pid >> 8);

        if (first) {
            p[-1] |= 0x40;
        }

        *p++ = (u_char) f->pid;
        *p++ = 0x10 | (f->cc & 0x0f); /* payload */

        if (first) {

            if (f->key) {
                packet[3] |= 0x20; /* adaptation */

                *p++ = 7;    /* size */
                *p++ = 0x50; /* random access + PCR */

                p = ngx_rtmp_mpegts_write_pcr(p, f->dts - NGX_RTMP_HLS_DELAY);
            }

            /* PES header */

            *p++ = 0x00;
            *p++ = 0x00;
            *p++ = 0x01;
            *p++ = (u_char) f->sid;

            header_size = 5;
            flags = 0x80; /* PTS */

            if (f->dts != f->pts) {
                header_size += 5;
                flags |= 0x40; /* DTS */
            }

            pes_size = (b->last - b->pos) + header_size + 3;
            if (pes_size > 0xffff) {
                pes_size = 0;
            }

            *p++ = (u_char) (pes_size >> 8);
            *p++ = (u_char) pes_size;
            *p++ = 0x80; /* H222 */
            *p++ = (u_char) flags;
            *p++ = (u_char) header_size;

            p = ngx_rtmp_mpegts_write_pts(p, flags >> 6, f->pts +
                                                         NGX_RTMP_HLS_DELAY);

            if (f->dts != f->pts) {
                p = ngx_rtmp_mpegts_write_pts(p, 1, f->dts +
                                                    NGX_RTMP_HLS_DELAY);
            }

            first = 0;
        }

        body_size = (ngx_uint_t) (packet + sizeof(packet) - p);
        in_size = (ngx_uint_t) (b->last - b->pos);

        if (body_size <= in_size) {
            ngx_memcpy(p, b->pos, body_size);
            b->pos += body_size;

        } else {
            stuff_size = (body_size - in_size);

            if (packet[3] & 0x20) {

                /* has adaptation */

                base = &packet[5] + packet[4];
                p = ngx_movemem(base + stuff_size, base, p - base);
                ngx_memset(base, 0xff, stuff_size);
                packet[4] += (u_char) stuff_size;

            } else {

                /* no adaptation */

                packet[3] |= 0x20;
                p = ngx_movemem(&packet[4] + stuff_size, &packet[4],
                                p - &packet[4]);

                packet[4] = (u_char) (stuff_size - 1);
                if (stuff_size >= 2) {
                    packet[5] = 0;
                    ngx_memset(&packet[6], 0xff, stuff_size - 2);
                }
            }

            ngx_memcpy(p, b->pos, in_size);
            b->pos = b->last;
        }

        rc = ngx_rtmp_mpegts_write_file(file, packet, sizeof(packet));
        if (rc != NGX_OK) {
            return rc;
        }
    }

    return NGX_OK;
}