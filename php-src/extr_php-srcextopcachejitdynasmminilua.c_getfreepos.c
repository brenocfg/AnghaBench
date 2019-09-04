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
struct TYPE_3__ {scalar_t__ node; int /*<<< orphan*/ * lastfree; } ;
typedef  TYPE_1__ Table ;
typedef  int /*<<< orphan*/  Node ;

/* Variables and functions */
 int /*<<< orphan*/  gkey (int /*<<< orphan*/ *) ; 
 scalar_t__ ttisnil (int /*<<< orphan*/ ) ; 

__attribute__((used)) static Node*getfreepos(Table*t){
while(t->lastfree-->t->node){
if(ttisnil(gkey(t->lastfree)))
return t->lastfree;
}
return NULL;
}