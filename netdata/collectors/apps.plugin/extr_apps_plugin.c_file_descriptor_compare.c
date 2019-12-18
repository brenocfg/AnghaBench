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
struct file_descriptor {int magic; scalar_t__ hash; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  error (char*) ; 
 int strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int file_descriptor_compare(void* a, void* b) {
#ifdef NETDATA_INTERNAL_CHECKS
    if(((struct file_descriptor *)a)->magic != 0x0BADCAFE || ((struct file_descriptor *)b)->magic != 0x0BADCAFE)
        error("Corrupted index data detected. Please report this.");
#endif /* NETDATA_INTERNAL_CHECKS */

    if(((struct file_descriptor *)a)->hash < ((struct file_descriptor *)b)->hash)
        return -1;

    else if(((struct file_descriptor *)a)->hash > ((struct file_descriptor *)b)->hash)
        return 1;

    else
        return strcmp(((struct file_descriptor *)a)->name, ((struct file_descriptor *)b)->name);
}