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
struct sis_video_info {scalar_t__ sisfb_id; scalar_t__ video_vbase; int /*<<< orphan*/  sisfb_heap; int /*<<< orphan*/  havenoheap; } ;
struct sis_memreq {scalar_t__ size; scalar_t__ offset; } ;
struct SIS_OH {scalar_t__ offset; scalar_t__ size; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTK (char*,...) ; 
 scalar_t__ SISFB_ID ; 
 struct SIS_OH* sisfb_poh_allocate (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
sis_int_malloc(struct sis_video_info *ivideo, struct sis_memreq *req)
{
	struct SIS_OH *poh = NULL;

	if((ivideo) && (ivideo->sisfb_id == SISFB_ID) && (!ivideo->havenoheap))
		poh = sisfb_poh_allocate(&ivideo->sisfb_heap, (u32)req->size);

	if(poh == NULL) {
		req->offset = req->size = 0;
		DPRINTK("sisfb: Video RAM allocation failed\n");
	} else {
		req->offset = poh->offset;
		req->size = poh->size;
		DPRINTK("sisfb: Video RAM allocation succeeded: 0x%lx\n",
			(poh->offset + ivideo->video_vbase));
	}
}