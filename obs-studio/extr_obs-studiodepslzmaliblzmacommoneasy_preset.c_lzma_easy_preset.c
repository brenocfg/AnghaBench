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
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_5__ {TYPE_1__* filters; int /*<<< orphan*/  opt_lzma; } ;
typedef  TYPE_2__ lzma_options_easy ;
struct TYPE_4__ {int /*<<< orphan*/  id; int /*<<< orphan*/ * options; } ;

/* Variables and functions */
 int /*<<< orphan*/  LZMA_FILTER_LZMA2 ; 
 int /*<<< orphan*/  LZMA_VLI_UNKNOWN ; 
 scalar_t__ lzma_lzma_preset (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

extern bool
lzma_easy_preset(lzma_options_easy *opt_easy, uint32_t preset)
{
	if (lzma_lzma_preset(&opt_easy->opt_lzma, preset))
		return true;

	opt_easy->filters[0].id = LZMA_FILTER_LZMA2;
	opt_easy->filters[0].options = &opt_easy->opt_lzma;
	opt_easy->filters[1].id = LZMA_VLI_UNKNOWN;

	return false;
}