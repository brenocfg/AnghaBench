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
struct keypairs_t {int keypairs_nb; void* keypairs; } ;

/* Variables and functions */
 void* malloc (int) ; 
 int /*<<< orphan*/  os_memset (struct keypairs_t*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static struct keypairs_t * enduser_setup_alloc_keypairs(int kp_number ){
    struct keypairs_t *kp = malloc(sizeof(struct keypairs_t));
    os_memset(kp, 0, sizeof(struct keypairs_t));

    kp->keypairs = malloc(kp_number * 2 * sizeof(char *));
    kp->keypairs_nb = kp_number;
    return kp;
}