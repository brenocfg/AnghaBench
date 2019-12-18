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
typedef  int /*<<< orphan*/  symbol ;
struct SN_env {int* I; unsigned char* B; int /*<<< orphan*/ ** S; int /*<<< orphan*/ * p; } ;

/* Variables and functions */
 int /*<<< orphan*/  SN_close_env (struct SN_env*,int) ; 
 scalar_t__ calloc (int,int) ; 
 void* create_s () ; 

extern struct SN_env * SN_create_env(int S_size, int I_size, int B_size)
{
    struct SN_env * z = (struct SN_env *) calloc(1, sizeof(struct SN_env));
    if (z == NULL) return NULL;
    z->p = create_s();
    if (z->p == NULL) goto error;
    if (S_size)
    {
        int i;
        z->S = (symbol * *) calloc(S_size, sizeof(symbol *));
        if (z->S == NULL) goto error;

        for (i = 0; i < S_size; i++)
        {
            z->S[i] = create_s();
            if (z->S[i] == NULL) goto error;
        }
    }

    if (I_size)
    {
        z->I = (int *) calloc(I_size, sizeof(int));
        if (z->I == NULL) goto error;
    }

    if (B_size)
    {
        z->B = (unsigned char *) calloc(B_size, sizeof(unsigned char));
        if (z->B == NULL) goto error;
    }

    return z;
error:
    SN_close_env(z, S_size);
    return NULL;
}