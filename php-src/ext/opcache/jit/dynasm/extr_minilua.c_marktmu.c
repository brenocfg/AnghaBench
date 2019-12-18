#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {TYPE_3__* tmudata; } ;
typedef  TYPE_2__ global_State ;
struct TYPE_9__ {TYPE_3__* next; } ;
struct TYPE_11__ {TYPE_1__ gch; } ;
typedef  TYPE_3__ GCObject ;

/* Variables and functions */
 int /*<<< orphan*/  makewhite (TYPE_2__*,TYPE_3__*) ; 
 int /*<<< orphan*/  reallymarkobject (TYPE_2__*,TYPE_3__*) ; 

__attribute__((used)) static void marktmu(global_State*g){
GCObject*u=g->tmudata;
if(u){
do{
u=u->gch.next;
makewhite(g,u);
reallymarkobject(g,u);
}while(u!=g->tmudata);
}
}