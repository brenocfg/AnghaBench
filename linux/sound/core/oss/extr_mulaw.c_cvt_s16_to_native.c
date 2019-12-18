#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  u16 ;
struct mulaw_priv {scalar_t__ native_bytes; scalar_t__ copy_bytes; int native_ofs; int copy_ofs; scalar_t__ cvt_endian; int /*<<< orphan*/  flip; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (unsigned char*,char*,scalar_t__) ; 
 int /*<<< orphan*/  memset (unsigned char*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  swab16 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void cvt_s16_to_native(struct mulaw_priv *data,
				     unsigned char *dst, u16 sample)
{
	sample ^= data->flip;
	if (data->cvt_endian)
		sample = swab16(sample);
	if (data->native_bytes > data->copy_bytes)
		memset(dst, 0, data->native_bytes);
	memcpy(dst + data->native_ofs, (char *)&sample + data->copy_ofs,
	       data->copy_bytes);
}