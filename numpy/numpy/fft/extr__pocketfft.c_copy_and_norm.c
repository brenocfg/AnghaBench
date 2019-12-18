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

/* Variables and functions */
 int /*<<< orphan*/  memcpy (double*,double*,size_t) ; 

__attribute__((used)) static void copy_and_norm(double *c, double *p1, size_t n, double fct)
  {
  if (p1!=c)
    {
    if (fct!=1.)
      for (size_t i=0; i<n; ++i)
        c[i] = fct*p1[i];
    else
      memcpy (c,p1,n*sizeof(double));
    }
  else
    if (fct!=1.)
      for (size_t i=0; i<n; ++i)
        c[i] *= fct;
  }