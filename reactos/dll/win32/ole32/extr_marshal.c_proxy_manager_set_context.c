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
struct proxy_manager {int dest_context; int /*<<< orphan*/  dest_context_data; } ;
typedef  int /*<<< orphan*/  PLONG ;
typedef  int MSHCTX ;

/* Variables and functions */
 int InterlockedCompareExchange (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  InterlockedExchangePointer (int /*<<< orphan*/ *,void*) ; 
#define  MSHCTX_CROSSCTX 132 
#define  MSHCTX_DIFFERENTMACHINE 131 
#define  MSHCTX_INPROC 130 
#define  MSHCTX_LOCAL 129 
#define  MSHCTX_NOSHAREDMEM 128 

__attribute__((used)) static inline void proxy_manager_set_context(struct proxy_manager *This, MSHCTX dest_context, void *dest_context_data)
{
    MSHCTX old_dest_context;
    MSHCTX new_dest_context;

    do
    {
        old_dest_context = This->dest_context;
        new_dest_context = old_dest_context;
        /* "stronger" values overwrite "weaker" values. stronger values are
         * ones that disable more optimisations */
        switch (old_dest_context)
        {
        case MSHCTX_INPROC:
            new_dest_context = dest_context;
            break;
        case MSHCTX_CROSSCTX:
            switch (dest_context)
            {
            case MSHCTX_INPROC:
                break;
            default:
                new_dest_context = dest_context;
            }
            break;
        case MSHCTX_LOCAL:
            switch (dest_context)
            {
            case MSHCTX_INPROC:
            case MSHCTX_CROSSCTX:
                break;
            default:
                new_dest_context = dest_context;
            }
            break;
        case MSHCTX_NOSHAREDMEM:
            switch (dest_context)
            {
            case MSHCTX_DIFFERENTMACHINE:
                new_dest_context = dest_context;
                break;
            default:
                break;
            }
            break;
        default:
            break;
        }

        if (old_dest_context == new_dest_context) break;

        new_dest_context = InterlockedCompareExchange((PLONG)&This->dest_context, new_dest_context, old_dest_context);
    } while (new_dest_context != old_dest_context);

    if (dest_context_data)
        InterlockedExchangePointer(&This->dest_context_data, dest_context_data);
}