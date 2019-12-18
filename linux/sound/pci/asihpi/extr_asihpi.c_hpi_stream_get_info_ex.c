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
 int /*<<< orphan*/  hpi_instream_get_info_ex (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hpi_outstream_get_info_ex (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline u16 hpi_stream_get_info_ex(
    u32 h_stream,
    u16        *pw_state,
    u32        *pbuffer_size,
    u32        *pdata_in_buffer,
    u32        *psample_count,
    u32        *pauxiliary_data
)
{
	u16 e;
	if (hpi_handle_object(h_stream)  ==  HPI_OBJ_OSTREAM)
		e = hpi_outstream_get_info_ex(h_stream, pw_state,
					pbuffer_size, pdata_in_buffer,
					psample_count, pauxiliary_data);
	else
		e = hpi_instream_get_info_ex(h_stream, pw_state,
					pbuffer_size, pdata_in_buffer,
					psample_count, pauxiliary_data);
	return e;
}