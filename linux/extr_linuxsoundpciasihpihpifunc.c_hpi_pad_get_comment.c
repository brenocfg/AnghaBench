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
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  u16 ;

/* Variables and functions */
 int /*<<< orphan*/  HPI_PAD_COMMENT ; 
 int /*<<< orphan*/  hpi_control_get_string (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/  const) ; 

u16 hpi_pad_get_comment(u32 h_control, char *psz_string,
	const u32 data_length)
{
	return hpi_control_get_string(h_control, HPI_PAD_COMMENT, psz_string,
		data_length);
}