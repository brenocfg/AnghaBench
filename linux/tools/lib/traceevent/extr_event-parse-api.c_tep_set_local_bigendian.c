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
struct tep_handle {int host_bigendian; } ;
typedef  enum tep_endian { ____Placeholder_tep_endian } tep_endian ;

/* Variables and functions */

void tep_set_local_bigendian(struct tep_handle *tep, enum tep_endian endian)
{
	if (tep)
		tep->host_bigendian = endian;
}