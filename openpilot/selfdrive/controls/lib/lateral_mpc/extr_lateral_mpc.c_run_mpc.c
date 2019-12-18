#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_5__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  delta; int /*<<< orphan*/  psi; int /*<<< orphan*/  y; int /*<<< orphan*/  x; } ;
typedef  TYPE_1__ state_t ;
struct TYPE_7__ {int /*<<< orphan*/  cost; int /*<<< orphan*/ * rate; int /*<<< orphan*/ * delta; int /*<<< orphan*/ * psi; int /*<<< orphan*/ * y; int /*<<< orphan*/ * x; } ;
typedef  TYPE_2__ log_t ;
struct TYPE_8__ {double* od; int /*<<< orphan*/ * u; int /*<<< orphan*/ * x; int /*<<< orphan*/ * x0; } ;

/* Variables and functions */
 int N ; 
 int NOD ; 
 int NX ; 
 TYPE_5__ acadoVariables ; 
 int /*<<< orphan*/  acado_feedbackStep () ; 
 int acado_getNWSR () ; 
 int /*<<< orphan*/  acado_getObjective () ; 
 int /*<<< orphan*/  acado_preparationStep () ; 

int run_mpc(state_t * x0, log_t * solution,
             double l_poly[4], double r_poly[4], double d_poly[4],
             double l_prob, double r_prob, double curvature_factor, double v_ref, double lane_width){

  int    i;

  for (i = 0; i <= NOD * N; i+= NOD){
    acadoVariables.od[i] = curvature_factor;
    acadoVariables.od[i+1] = v_ref;

    acadoVariables.od[i+2] = l_poly[0];
    acadoVariables.od[i+3] = l_poly[1];
    acadoVariables.od[i+4] = l_poly[2];
    acadoVariables.od[i+5] = l_poly[3];

    acadoVariables.od[i+6] = r_poly[0];
    acadoVariables.od[i+7] = r_poly[1];
    acadoVariables.od[i+8] = r_poly[2];
    acadoVariables.od[i+9] = r_poly[3];

    acadoVariables.od[i+10] = d_poly[0];
    acadoVariables.od[i+11] = d_poly[1];
    acadoVariables.od[i+12] = d_poly[2];
    acadoVariables.od[i+13] = d_poly[3];


    acadoVariables.od[i+14] = l_prob;
    acadoVariables.od[i+15] = r_prob;
    acadoVariables.od[i+16] = lane_width;

  }

  acadoVariables.x0[0] = x0->x;
  acadoVariables.x0[1] = x0->y;
  acadoVariables.x0[2] = x0->psi;
  acadoVariables.x0[3] = x0->delta;


  acado_preparationStep();
  acado_feedbackStep();

  /* printf("lat its: %d\n", acado_getNWSR());  // n iterations
  printf("Objective: %.6f\n", acado_getObjective());  // solution cost */

  for (i = 0; i <= N; i++){
    solution->x[i] = acadoVariables.x[i*NX];
    solution->y[i] = acadoVariables.x[i*NX+1];
    solution->psi[i] = acadoVariables.x[i*NX+2];
    solution->delta[i] = acadoVariables.x[i*NX+3];
    if (i < N){
      solution->rate[i] = acadoVariables.u[i];
    }
  }
  solution->cost = acado_getObjective();

  // Dont shift states here. Current solution is closer to next timestep than if
  // we use the old solution as a starting point
  //acado_shiftStates(2, 0, 0);
  //acado_shiftControls( 0 );

  return acado_getNWSR();
}