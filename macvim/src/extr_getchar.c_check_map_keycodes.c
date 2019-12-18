#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int* m_keys; int* m_str; struct TYPE_6__* m_next; } ;
typedef  TYPE_1__ mapblock_T ;
typedef  int char_u ;
struct TYPE_7__ {TYPE_1__** b_maphash; TYPE_1__* b_first_abbr; struct TYPE_7__* b_next; } ;
typedef  TYPE_2__ buf_T ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int K_SPECIAL ; 
 int NUL ; 
 int /*<<< orphan*/  add_termcap_entry (int*,int /*<<< orphan*/ ) ; 
 TYPE_1__* first_abbr ; 
 TYPE_2__* firstbuf ; 
 TYPE_1__** maphash ; 
 int* sourcing_name ; 
 int /*<<< orphan*/  validate_maphash () ; 

void
check_map_keycodes()
{
    mapblock_T	*mp;
    char_u	*p;
    int		i;
    char_u	buf[3];
    char_u	*save_name;
    int		abbr;
    int		hash;
#ifdef FEAT_LOCALMAP
    buf_T	*bp;
#endif

    validate_maphash();
    save_name = sourcing_name;
    sourcing_name = (char_u *)"mappings"; /* avoids giving error messages */

#ifdef FEAT_LOCALMAP
    /* This this once for each buffer, and then once for global
     * mappings/abbreviations with bp == NULL */
    for (bp = firstbuf; ; bp = bp->b_next)
    {
#endif
	/*
	 * Do the loop twice: Once for mappings, once for abbreviations.
	 * Then loop over all map hash lists.
	 */
	for (abbr = 0; abbr <= 1; ++abbr)
	    for (hash = 0; hash < 256; ++hash)
	    {
		if (abbr)
		{
		    if (hash)	    /* there is only one abbr list */
			break;
#ifdef FEAT_LOCALMAP
		    if (bp != NULL)
			mp = bp->b_first_abbr;
		    else
#endif
			mp = first_abbr;
		}
		else
		{
#ifdef FEAT_LOCALMAP
		    if (bp != NULL)
			mp = bp->b_maphash[hash];
		    else
#endif
			mp = maphash[hash];
		}
		for ( ; mp != NULL; mp = mp->m_next)
		{
		    for (i = 0; i <= 1; ++i)	/* do this twice */
		    {
			if (i == 0)
			    p = mp->m_keys;	/* once for the "from" part */
			else
			    p = mp->m_str;	/* and once for the "to" part */
			while (*p)
			{
			    if (*p == K_SPECIAL)
			    {
				++p;
				if (*p < 128)   /* for "normal" tcap entries */
				{
				    buf[0] = p[0];
				    buf[1] = p[1];
				    buf[2] = NUL;
				    (void)add_termcap_entry(buf, FALSE);
				}
				++p;
			    }
			    ++p;
			}
		    }
		}
	    }
#ifdef FEAT_LOCALMAP
	if (bp == NULL)
	    break;
    }
#endif
    sourcing_name = save_name;
}