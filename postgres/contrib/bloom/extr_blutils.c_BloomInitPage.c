#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint16 ;
struct TYPE_4__ {int /*<<< orphan*/  bloom_page_id; int /*<<< orphan*/  flags; } ;
typedef  int /*<<< orphan*/  Page ;
typedef  int /*<<< orphan*/  BloomPageOpaqueData ;
typedef  TYPE_1__* BloomPageOpaque ;

/* Variables and functions */
 int /*<<< orphan*/  BLCKSZ ; 
 int /*<<< orphan*/  BLOOM_PAGE_ID ; 
 TYPE_1__* BloomPageGetOpaque (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PageInit (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

void
BloomInitPage(Page page, uint16 flags)
{
	BloomPageOpaque opaque;

	PageInit(page, BLCKSZ, sizeof(BloomPageOpaqueData));

	opaque = BloomPageGetOpaque(page);
	memset(opaque, 0, sizeof(BloomPageOpaqueData));
	opaque->flags = flags;
	opaque->bloom_page_id = BLOOM_PAGE_ID;
}