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
 scalar_t__ HPI_OBJ_OSTREAM ; 
 scalar_t__ hpi_handle_object (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hpi_instream_group_add (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hpi_outstream_group_add (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline u16 hpi_stream_group_add(
					u32 h_master,
					u32 h_stream)
{
	if (hpi_handle_object(h_master) ==  HPI_OBJ_OSTREAM)
		return hpi_outstream_group_add(h_master, h_stream);
	else
		return hpi_instream_group_add(h_master, h_stream);
}