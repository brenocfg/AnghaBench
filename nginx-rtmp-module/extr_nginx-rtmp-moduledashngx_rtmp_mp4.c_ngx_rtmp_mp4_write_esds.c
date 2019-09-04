#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_char ;
typedef  int /*<<< orphan*/  ngx_rtmp_session_t ;
struct TYPE_15__ {TYPE_1__* aac_header; } ;
typedef  TYPE_2__ ngx_rtmp_codec_ctx_t ;
typedef  int /*<<< orphan*/  ngx_int_t ;
struct TYPE_16__ {int /*<<< orphan*/ * last; int /*<<< orphan*/ * pos; } ;
typedef  TYPE_3__ ngx_buf_t ;
struct TYPE_14__ {TYPE_3__* buf; } ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_ERROR ; 
 int /*<<< orphan*/  NGX_OK ; 
 int /*<<< orphan*/  ngx_rtmp_codec_module ; 
 TYPE_2__* ngx_rtmp_get_module_ctx (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_rtmp_mp4_data (TYPE_3__*,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  ngx_rtmp_mp4_field_16 (TYPE_3__*,int) ; 
 int /*<<< orphan*/  ngx_rtmp_mp4_field_24 (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_rtmp_mp4_field_32 (TYPE_3__*,int) ; 
 int /*<<< orphan*/  ngx_rtmp_mp4_field_8 (TYPE_3__*,int) ; 
 int /*<<< orphan*/  ngx_rtmp_mp4_put_descr (TYPE_3__*,int,int) ; 
 int /*<<< orphan*/ * ngx_rtmp_mp4_start_box (TYPE_3__*,char*) ; 
 int /*<<< orphan*/  ngx_rtmp_mp4_update_box_size (TYPE_3__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static ngx_int_t
ngx_rtmp_mp4_write_esds(ngx_rtmp_session_t *s, ngx_buf_t *b)
{
    size_t                 dsi_len;
    u_char                *pos, *dsi;
    ngx_buf_t             *db;
    ngx_rtmp_codec_ctx_t  *codec_ctx;

    codec_ctx = ngx_rtmp_get_module_ctx(s, ngx_rtmp_codec_module);

    if (codec_ctx == NULL || codec_ctx->aac_header == NULL) {
        return NGX_ERROR;
    }

    db = codec_ctx->aac_header->buf;
    if (db == NULL) {
        return NGX_ERROR;
    }

    dsi = db->pos + 2;
    if (dsi > db->last) {
        return NGX_ERROR;
    }

    dsi_len = db->last - dsi;

    pos = ngx_rtmp_mp4_start_box(b, "esds");

    /* version */
    ngx_rtmp_mp4_field_32(b, 0);


    /* ES Descriptor */

    ngx_rtmp_mp4_put_descr(b, 0x03, 23 + dsi_len);

    /* ES_ID */
    ngx_rtmp_mp4_field_16(b, 1);

    /* flags */
    ngx_rtmp_mp4_field_8(b, 0);


    /* DecoderConfig Descriptor */

    ngx_rtmp_mp4_put_descr(b, 0x04, 15 + dsi_len);

    /* objectTypeIndication: Audio ISO/IEC 14496-3 (AAC) */
    ngx_rtmp_mp4_field_8(b, 0x40);

    /* streamType: AudioStream */
    ngx_rtmp_mp4_field_8(b, 0x15);

    /* bufferSizeDB */
    ngx_rtmp_mp4_field_24(b, 0);

    /* maxBitrate */
    ngx_rtmp_mp4_field_32(b, 0x0001F151);

    /* avgBitrate */
    ngx_rtmp_mp4_field_32(b, 0x0001F14D);


    /* DecoderSpecificInfo Descriptor */

    ngx_rtmp_mp4_put_descr(b, 0x05, dsi_len);
    ngx_rtmp_mp4_data(b, dsi, dsi_len);


    /* SL Descriptor */

    ngx_rtmp_mp4_put_descr(b, 0x06, 1);
    ngx_rtmp_mp4_field_8(b, 0x02);

    ngx_rtmp_mp4_update_box_size(b, pos);

    return NGX_OK;
}