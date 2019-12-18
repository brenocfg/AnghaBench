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
struct SN_env {int c; scalar_t__* B; } ;

/* Variables and functions */
 int r_fix_ending (struct SN_env*) ; 
 int r_has_min_length (struct SN_env*) ; 
 int r_remove_command_suffixes (struct SN_env*) ; 
 int r_remove_common_word_endings (struct SN_env*) ; 
 int r_remove_plural_suffix (struct SN_env*) ; 
 int r_remove_pronoun_prefixes (struct SN_env*) ; 
 int r_remove_question_prefixes (struct SN_env*) ; 
 int r_remove_question_suffixes (struct SN_env*) ; 
 int r_remove_tense_suffixes (struct SN_env*) ; 
 int r_remove_um (struct SN_env*) ; 
 int r_remove_vetrumai_urupukal (struct SN_env*) ; 

extern int tamil_UTF_8_stem(struct SN_env * z) { /* forwardmode */
    z->B[1] = 0; /* unset found_vetrumai_urupu, line 393 */
    {   int c1 = z->c; /* do, line 394 */
        {   int ret = r_fix_ending(z); /* call fix_ending, line 394 */
            if (ret == 0) goto lab0;
            if (ret < 0) return ret;
        }
    lab0:
        z->c = c1;
    }
    {   int ret = r_has_min_length(z); /* call has_min_length, line 395 */
        if (ret <= 0) return ret;
    }
    {   int c2 = z->c; /* do, line 396 */
        {   int ret = r_remove_question_prefixes(z); /* call remove_question_prefixes, line 396 */
            if (ret == 0) goto lab1;
            if (ret < 0) return ret;
        }
    lab1:
        z->c = c2;
    }
    {   int c3 = z->c; /* do, line 397 */
        {   int ret = r_remove_pronoun_prefixes(z); /* call remove_pronoun_prefixes, line 397 */
            if (ret == 0) goto lab2;
            if (ret < 0) return ret;
        }
    lab2:
        z->c = c3;
    }
    {   int c4 = z->c; /* do, line 398 */
        {   int ret = r_remove_question_suffixes(z); /* call remove_question_suffixes, line 398 */
            if (ret == 0) goto lab3;
            if (ret < 0) return ret;
        }
    lab3:
        z->c = c4;
    }
    {   int c5 = z->c; /* do, line 399 */
        {   int ret = r_remove_um(z); /* call remove_um, line 399 */
            if (ret == 0) goto lab4;
            if (ret < 0) return ret;
        }
    lab4:
        z->c = c5;
    }
    {   int c6 = z->c; /* do, line 400 */
        {   int ret = r_remove_common_word_endings(z); /* call remove_common_word_endings, line 400 */
            if (ret == 0) goto lab5;
            if (ret < 0) return ret;
        }
    lab5:
        z->c = c6;
    }
    {   int c7 = z->c; /* do, line 401 */
        {   int ret = r_remove_vetrumai_urupukal(z); /* call remove_vetrumai_urupukal, line 401 */
            if (ret == 0) goto lab6;
            if (ret < 0) return ret;
        }
    lab6:
        z->c = c7;
    }
    {   int c8 = z->c; /* do, line 402 */
        {   int ret = r_remove_plural_suffix(z); /* call remove_plural_suffix, line 402 */
            if (ret == 0) goto lab7;
            if (ret < 0) return ret;
        }
    lab7:
        z->c = c8;
    }
    {   int c9 = z->c; /* do, line 403 */
        {   int ret = r_remove_command_suffixes(z); /* call remove_command_suffixes, line 403 */
            if (ret == 0) goto lab8;
            if (ret < 0) return ret;
        }
    lab8:
        z->c = c9;
    }
    {   int c10 = z->c; /* do, line 404 */
        {   int ret = r_remove_tense_suffixes(z); /* call remove_tense_suffixes, line 404 */
            if (ret == 0) goto lab9;
            if (ret < 0) return ret;
        }
    lab9:
        z->c = c10;
    }
    return 1;
}