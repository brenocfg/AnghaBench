#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {double* x; double* u; double* y; double* yN; double* x0; double* W; double* WN; } ;

/* Variables and functions */
 int N ; 
 int NU ; 
 int NX ; 
 int NY ; 
 int NYN ; 
 TYPE_1__ acadoVariables ; 
 int /*<<< orphan*/  acado_initializeSolver () ; 

void init(double pathCost, double laneCost, double headingCost, double steerRateCost){
  acado_initializeSolver();
  int    i;
  const int STEP_MULTIPLIER = 3;

  /* Initialize the states and controls. */
  for (i = 0; i < NX * (N + 1); ++i)  acadoVariables.x[ i ] = 0.0;
  for (i = 0; i < NU * N; ++i)  acadoVariables.u[ i ] = 0.1;

  /* Initialize the measurements/reference. */
  for (i = 0; i < NY * N; ++i)  acadoVariables.y[ i ] = 0.0;
  for (i = 0; i < NYN; ++i)  acadoVariables.yN[ i ] = 0.0;

  /* MPC: initialize the current state feedback. */
  for (i = 0; i < NX; ++i) acadoVariables.x0[ i ] = 0.0;

  for (i = 0; i < N; i++) {
    int f = 1;
    if (i > 4){
      f = STEP_MULTIPLIER;
    }
    // Setup diagonal entries
    acadoVariables.W[NY*NY*i + (NY+1)*0] = pathCost * f;
    acadoVariables.W[NY*NY*i + (NY+1)*1] = laneCost * f;
    acadoVariables.W[NY*NY*i + (NY+1)*2] = laneCost * f;
    acadoVariables.W[NY*NY*i + (NY+1)*3] = headingCost * f;
    acadoVariables.W[NY*NY*i + (NY+1)*4] = steerRateCost * f;
  }
  acadoVariables.WN[(NYN+1)*0] = pathCost * STEP_MULTIPLIER;
  acadoVariables.WN[(NYN+1)*1] = laneCost * STEP_MULTIPLIER;
  acadoVariables.WN[(NYN+1)*2] = laneCost * STEP_MULTIPLIER;
  acadoVariables.WN[(NYN+1)*3] = headingCost * STEP_MULTIPLIER;
}