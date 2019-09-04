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
struct web_client {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  guid; } ;
typedef  TYPE_1__ REGISTRY_PERSON ;

/* Variables and functions */
 int /*<<< orphan*/  registry_set_cookie (struct web_client*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void registry_set_person_cookie(struct web_client *w, REGISTRY_PERSON *p) {
    registry_set_cookie(w, p->guid);
}