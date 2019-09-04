#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {unsigned char* buf; } ;
typedef  TYPE_1__ loopargs_t ;

/* Variables and functions */
 scalar_t__ COND (int) ; 
 int /*<<< orphan*/  EVP_Digest (unsigned char*,int,unsigned char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int EVP_MAX_MD_SIZE ; 
 int /*<<< orphan*/  evp_md ; 
 int* lengths ; 
 int save_count ; 
 size_t testnum ; 

__attribute__((used)) static int EVP_Digest_loop(void *args)
{
    loopargs_t *tempargs = *(loopargs_t **) args;
    unsigned char *buf = tempargs->buf;
    unsigned char md[EVP_MAX_MD_SIZE];
    int count;
#ifndef SIGALRM
    int nb_iter = save_count * 4 * lengths[0] / lengths[testnum];
#endif

    for (count = 0; COND(nb_iter); count++) {
        if (!EVP_Digest(buf, lengths[testnum], md, NULL, evp_md, NULL))
            return -1;
    }
    return count;
}