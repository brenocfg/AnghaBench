#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__* buf; } ;
struct TYPE_3__ {int size; } ;
struct xz_dec {scalar_t__ check_type; TYPE_2__ temp; TYPE_1__ index; } ;
typedef  enum xz_ret { ____Placeholder_xz_ret } xz_ret ;

/* Variables and functions */
 int /*<<< orphan*/  FOOTER_MAGIC ; 
 int /*<<< orphan*/  FOOTER_MAGIC_SIZE ; 
 int XZ_DATA_ERROR ; 
 int XZ_STREAM_END ; 
 int get_le32 (scalar_t__*) ; 
 int /*<<< orphan*/  memeq (scalar_t__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int xz_crc32 (scalar_t__*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static enum xz_ret dec_stream_footer(struct xz_dec *s)
{
	if (!memeq(s->temp.buf + 10, FOOTER_MAGIC, FOOTER_MAGIC_SIZE))
		return XZ_DATA_ERROR;

	if (xz_crc32(s->temp.buf + 4, 6, 0) != get_le32(s->temp.buf))
		return XZ_DATA_ERROR;

	/*
	 * Validate Backward Size. Note that we never added the size of the
	 * Index CRC32 field to s->index.size, thus we use s->index.size / 4
	 * instead of s->index.size / 4 - 1.
	 */
	if ((s->index.size >> 2) != get_le32(s->temp.buf + 4))
		return XZ_DATA_ERROR;

	if (s->temp.buf[8] != 0 || s->temp.buf[9] != s->check_type)
		return XZ_DATA_ERROR;

	/*
	 * Use XZ_STREAM_END instead of XZ_OK to be more convenient
	 * for the caller.
	 */
	return XZ_STREAM_END;
}