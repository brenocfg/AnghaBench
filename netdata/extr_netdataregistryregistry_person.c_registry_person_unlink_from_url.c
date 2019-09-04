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
typedef  int /*<<< orphan*/  REGISTRY_PERSON_URL ;
typedef  int /*<<< orphan*/  REGISTRY_PERSON ;

/* Variables and functions */
 int /*<<< orphan*/  registry_person_url_free (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void registry_person_unlink_from_url(REGISTRY_PERSON *p, REGISTRY_PERSON_URL *pu) {
    registry_person_url_free(p, pu);
}