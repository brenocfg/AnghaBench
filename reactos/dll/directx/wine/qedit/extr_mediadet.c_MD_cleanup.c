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
struct TYPE_3__ {int num_streams; scalar_t__ cur_stream; int /*<<< orphan*/ * graph; int /*<<< orphan*/ * splitter; int /*<<< orphan*/ * source; int /*<<< orphan*/ * cur_pin; } ;
typedef  TYPE_1__ MediaDetImpl ;

/* Variables and functions */
 int /*<<< orphan*/  IBaseFilter_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IGraphBuilder_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IPin_Release (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void MD_cleanup(MediaDetImpl *This)
{
    if (This->cur_pin) IPin_Release(This->cur_pin);
    This->cur_pin = NULL;
    if (This->source) IBaseFilter_Release(This->source);
    This->source = NULL;
    if (This->splitter) IBaseFilter_Release(This->splitter);
    This->splitter = NULL;
    if (This->graph) IGraphBuilder_Release(This->graph);
    This->graph = NULL;
    This->num_streams = -1;
    This->cur_stream = 0;
}