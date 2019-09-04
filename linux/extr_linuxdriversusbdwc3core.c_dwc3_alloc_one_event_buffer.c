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
struct dwc3_event_buffer {unsigned int length; int /*<<< orphan*/  buf; int /*<<< orphan*/  dma; void* cache; struct dwc3* dwc; } ;
struct dwc3 {int /*<<< orphan*/  sysdev; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 struct dwc3_event_buffer* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 void* devm_kzalloc (int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_alloc_coherent (int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct dwc3_event_buffer *dwc3_alloc_one_event_buffer(struct dwc3 *dwc,
		unsigned length)
{
	struct dwc3_event_buffer	*evt;

	evt = devm_kzalloc(dwc->dev, sizeof(*evt), GFP_KERNEL);
	if (!evt)
		return ERR_PTR(-ENOMEM);

	evt->dwc	= dwc;
	evt->length	= length;
	evt->cache	= devm_kzalloc(dwc->dev, length, GFP_KERNEL);
	if (!evt->cache)
		return ERR_PTR(-ENOMEM);

	evt->buf	= dma_alloc_coherent(dwc->sysdev, length,
			&evt->dma, GFP_KERNEL);
	if (!evt->buf)
		return ERR_PTR(-ENOMEM);

	return evt;
}