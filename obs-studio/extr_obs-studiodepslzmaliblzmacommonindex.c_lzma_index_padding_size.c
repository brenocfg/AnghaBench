#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct TYPE_3__ {int /*<<< orphan*/  index_list_size; int /*<<< orphan*/  record_count; } ;
typedef  TYPE_1__ lzma_index ;

/* Variables and functions */
 int LZMA_VLI_C (int) ; 
 int index_size_unpadded (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

extern uint32_t
lzma_index_padding_size(const lzma_index *i)
{
	return (LZMA_VLI_C(4) - index_size_unpadded(
			i->record_count, i->index_list_size)) & 3;
}