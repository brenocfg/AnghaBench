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
struct TYPE_2__ {double* x; double* u; double* y; double* yN; } ;

/* Variables and functions */
 int N ; 
 int NU ; 
 int NX ; 
 int NY ; 
 int NYN ; 
 TYPE_1__ acadoVariables ; 

void init_with_simulation(double v_ego, double x_l_0, double v_l_0, double a_l_0, double l){
  int i;

  double x_l = x_l_0;
  double v_l = v_l_0;
  double a_l = a_l_0;

  double x_ego = 0.0;
  double a_ego = -(v_ego - v_l) * (v_ego - v_l) / (2.0 * x_l + 0.01) + a_l;

  if (a_ego > 0){
    a_ego = 0.0;
  }


  double dt = 0.2;
  double t = 0.;

  for (i = 0; i < N + 1; ++i){
    if (i > 4){
      dt = 0.6;
    }

    /* printf("%.2f\t%.2f\t%.2f\t%.2f\n", t, x_ego, v_ego, a_l); */
    acadoVariables.x[i*NX] = x_ego;
    acadoVariables.x[i*NX+1] = v_ego;
    acadoVariables.x[i*NX+2] = a_ego;

    v_ego += a_ego * dt;

    if (v_ego <= 0.0) {
      v_ego = 0.0;
      a_ego = 0.0;
    }

    x_ego += v_ego * dt;
    t += dt;
  }

  for (i = 0; i < NU * N; ++i)  acadoVariables.u[ i ] = 0.0;
  for (i = 0; i < NY * N; ++i)  acadoVariables.y[ i ] = 0.0;
  for (i = 0; i < NYN; ++i)  acadoVariables.yN[ i ] = 0.0;
}