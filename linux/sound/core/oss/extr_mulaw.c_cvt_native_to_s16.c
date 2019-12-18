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
typedef  scalar_t__ u16 ;
struct mulaw_priv {int copy_ofs; int native_ofs; scalar_t__ flip; scalar_t__ cvt_endian; int /*<<< orphan*/  copy_bytes; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (char*,unsigned char*,int /*<<< orphan*/ ) ; 
 scalar_t__ swab16 (scalar_t__) ; 

__attribute__((used)) static inline signed short cvt_native_to_s16(struct mulaw_priv *data,
					     unsigned char *src)
{
	u16 sample = 0;
	memcpy((char *)&sample + data->copy_ofs, src + data->native_ofs,
	       data->copy_bytes);
	if (data->cvt_endian)
		sample = swab16(sample);
	sample ^= data->flip;
	return (signed short)sample;
}