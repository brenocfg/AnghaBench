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
struct SN_env {int lb; int c; int l; int /*<<< orphan*/ * B; } ;

/* Variables and functions */
 int r_more_than_one_syllable_word (struct SN_env*) ; 
 int r_postlude (struct SN_env*) ; 
 int r_stem_nominal_verb_suffixes (struct SN_env*) ; 
 int r_stem_noun_suffixes (struct SN_env*) ; 

extern int turkish_UTF_8_stem(struct SN_env * z) { /* forwardmode */
    {   int ret = r_more_than_one_syllable_word(z); /* call more_than_one_syllable_word, line 460 */
        if (ret <= 0) return ret;
    }
    z->lb = z->c; z->c = z->l; /* backwards, line 462 */

    {   int m1 = z->l - z->c; (void)m1; /* do, line 463 */
        {   int ret = r_stem_nominal_verb_suffixes(z); /* call stem_nominal_verb_suffixes, line 463 */
            if (ret == 0) goto lab0;
            if (ret < 0) return ret;
        }
    lab0:
        z->c = z->l - m1;
    }
    if (!(z->B[0])) return 0; /* Boolean test continue_stemming_noun_suffixes, line 464 */
    {   int m2 = z->l - z->c; (void)m2; /* do, line 465 */
        {   int ret = r_stem_noun_suffixes(z); /* call stem_noun_suffixes, line 465 */
            if (ret == 0) goto lab1;
            if (ret < 0) return ret;
        }
    lab1:
        z->c = z->l - m2;
    }
    z->c = z->lb;
    {   int ret = r_postlude(z); /* call postlude, line 468 */
        if (ret <= 0) return ret;
    }
    return 1;
}