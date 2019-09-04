#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int ncommands; int ccommands; float* commands; float commandx; float commandy; } ;
struct TYPE_6__ {int /*<<< orphan*/  xform; } ;
typedef  TYPE_1__ NVGstate ;
typedef  TYPE_2__ NVGcontext ;

/* Variables and functions */
#define  NVG_BEZIERTO 132 
#define  NVG_CLOSE 131 
#define  NVG_LINETO 130 
#define  NVG_MOVETO 129 
#define  NVG_WINDING 128 
 int /*<<< orphan*/  memcpy (float*,float*,int) ; 
 int /*<<< orphan*/  nvgTransformPoint (float*,float*,int /*<<< orphan*/ ,float,float) ; 
 TYPE_1__* nvg__getState (TYPE_2__*) ; 
 scalar_t__ realloc (float*,int) ; 

__attribute__((used)) static void nvg__appendCommands(NVGcontext* ctx, float* vals, int nvals)
{
	NVGstate* state = nvg__getState(ctx);
	int i;

	if (ctx->ncommands+nvals > ctx->ccommands) {
		float* commands;
		int ccommands = ctx->ncommands+nvals + ctx->ccommands/2;
		commands = (float*)realloc(ctx->commands, sizeof(float)*ccommands);
		if (commands == NULL) return;
		ctx->commands = commands;
		ctx->ccommands = ccommands;
	}

	if ((int)vals[0] != NVG_CLOSE && (int)vals[0] != NVG_WINDING) {
		ctx->commandx = vals[nvals-2];
		ctx->commandy = vals[nvals-1];
	}

	// transform commands
	i = 0;
	while (i < nvals) {
		int cmd = (int)vals[i];
		switch (cmd) {
		case NVG_MOVETO:
			nvgTransformPoint(&vals[i+1],&vals[i+2], state->xform, vals[i+1],vals[i+2]);
			i += 3;
			break;
		case NVG_LINETO:
			nvgTransformPoint(&vals[i+1],&vals[i+2], state->xform, vals[i+1],vals[i+2]);
			i += 3;
			break;
		case NVG_BEZIERTO:
			nvgTransformPoint(&vals[i+1],&vals[i+2], state->xform, vals[i+1],vals[i+2]);
			nvgTransformPoint(&vals[i+3],&vals[i+4], state->xform, vals[i+3],vals[i+4]);
			nvgTransformPoint(&vals[i+5],&vals[i+6], state->xform, vals[i+5],vals[i+6]);
			i += 7;
			break;
		case NVG_CLOSE:
			i++;
			break;
		case NVG_WINDING:
			i += 2;
			break;
		default:
			i++;
		}
	}

	memcpy(&ctx->commands[ctx->ncommands], vals, nvals*sizeof(float));

	ctx->ncommands += nvals;
}