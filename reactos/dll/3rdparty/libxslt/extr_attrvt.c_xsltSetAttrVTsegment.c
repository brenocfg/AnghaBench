#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* xsltAttrVTPtr ;
typedef  int /*<<< orphan*/  xsltAttrVT ;
struct TYPE_5__ {int nb_seg; int max_seg; void** segments; } ;

/* Variables and functions */
 int MAX_AVT_SEG ; 
 int /*<<< orphan*/  memset (void**,int /*<<< orphan*/ ,int) ; 
 scalar_t__ xmlRealloc (TYPE_1__*,int) ; 

__attribute__((used)) static xsltAttrVTPtr
xsltSetAttrVTsegment(xsltAttrVTPtr avt, void *val) {
    if (avt->nb_seg >= avt->max_seg) {
	avt = (xsltAttrVTPtr) xmlRealloc(avt, sizeof(xsltAttrVT) +
			avt->max_seg * sizeof(void *));
	if (avt == NULL) {
	    return NULL;
	}
	memset(&avt->segments[avt->nb_seg], 0, MAX_AVT_SEG*sizeof(void *));
	avt->max_seg += MAX_AVT_SEG;
    }
    avt->segments[avt->nb_seg++] = val;
    return avt;
}