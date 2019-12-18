#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
struct TYPE_4__ {TYPE_1__* url; } ;
struct TYPE_3__ {scalar_t__ hash; int /*<<< orphan*/  url; } ;
typedef  TYPE_2__ REGISTRY_PERSON_URL ;

/* Variables and functions */
 int strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int person_url_compare(void *a, void *b) {
    register uint32_t hash1 = ((REGISTRY_PERSON_URL *)a)->url->hash;
    register uint32_t hash2 = ((REGISTRY_PERSON_URL *)b)->url->hash;

    if(hash1 < hash2) return -1;
    else if(hash1 > hash2) return 1;
    else return strcmp(((REGISTRY_PERSON_URL *)a)->url->url, ((REGISTRY_PERSON_URL *)b)->url->url);
}