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
 int /*<<< orphan*/  hpi_instream_start (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hpi_outstream_start (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline u16 hpi_stream_start(u32 h_stream)
{
	if (hpi_handle_object(h_stream) ==  HPI_OBJ_OSTREAM)
		return hpi_outstream_start(h_stream);
	else
		return hpi_instream_start(h_stream);
}