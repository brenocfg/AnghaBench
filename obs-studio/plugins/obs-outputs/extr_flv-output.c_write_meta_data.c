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
typedef  int /*<<< orphan*/  uint8_t ;
struct flv_output {int /*<<< orphan*/  file; int /*<<< orphan*/  output; } ;

/* Variables and functions */
 int /*<<< orphan*/  bfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  flv_meta_data (int /*<<< orphan*/ ,int /*<<< orphan*/ **,size_t*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fwrite (int /*<<< orphan*/ *,int,size_t,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void write_meta_data(struct flv_output *stream)
{
	uint8_t *meta_data;
	size_t meta_data_size;

	flv_meta_data(stream->output, &meta_data, &meta_data_size, true, 0);
	fwrite(meta_data, 1, meta_data_size, stream->file);
	bfree(meta_data);
}