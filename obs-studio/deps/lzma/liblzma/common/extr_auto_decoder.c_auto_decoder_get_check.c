#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  coder; int /*<<< orphan*/  (* get_check ) (int /*<<< orphan*/ ) ;} ;
struct TYPE_5__ {TYPE_1__ next; } ;
typedef  TYPE_2__ lzma_coder ;
typedef  int /*<<< orphan*/  lzma_check ;

/* Variables and functions */
 int /*<<< orphan*/  LZMA_CHECK_NONE ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static lzma_check
auto_decoder_get_check(const lzma_coder *coder)
{
	// It is LZMA_Alone if get_check is NULL.
	return coder->next.get_check == NULL ? LZMA_CHECK_NONE
			: coder->next.get_check(coder->next.coder);
}