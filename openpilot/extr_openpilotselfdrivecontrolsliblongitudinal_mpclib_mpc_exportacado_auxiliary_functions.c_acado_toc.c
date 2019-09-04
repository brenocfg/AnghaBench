#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct timeval {scalar_t__ tv_usec; scalar_t__ tv_sec; } ;
typedef  int real_t ;
struct TYPE_5__ {scalar_t__ tv_usec; scalar_t__ tv_sec; } ;
struct TYPE_7__ {scalar_t__ tv_usec; scalar_t__ tv_sec; } ;
struct TYPE_6__ {TYPE_1__ tic; TYPE_3__ toc; } ;
typedef  TYPE_2__ acado_timer ;

/* Variables and functions */
 int /*<<< orphan*/  gettimeofday (TYPE_3__*,int /*<<< orphan*/ ) ; 

real_t acado_toc( acado_timer* t )
{
	struct timeval temp;
	
	gettimeofday(&t->toc, 0);
    
	if ((t->toc.tv_usec - t->tic.tv_usec) < 0)
	{
		temp.tv_sec = t->toc.tv_sec - t->tic.tv_sec - 1;
		temp.tv_usec = 1000000 + t->toc.tv_usec - t->tic.tv_usec;
	}
	else
	{
		temp.tv_sec = t->toc.tv_sec - t->tic.tv_sec;
		temp.tv_usec = t->toc.tv_usec - t->tic.tv_usec;
	}
	
	return (real_t)temp.tv_sec + (real_t)temp.tv_usec / 1e6;
}