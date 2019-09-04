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
struct ring {int /*<<< orphan*/  (* walk ) (int,struct ring*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (int,struct ring*) ; 

__attribute__((used)) static void walk_ring(int sock, struct ring *ring)
{
	ring->walk(sock, ring);
}