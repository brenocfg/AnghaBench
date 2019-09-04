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
struct SmackPattern {unsigned int pattern_length; int is_anchor_begin; int is_anchor_end; int is_snmp_hack; int is_wildcards; size_t id; int /*<<< orphan*/  pattern; } ;
struct SMACK {int is_anchor_begin; int is_anchor_end; int m_pattern_count; int m_pattern_max; struct SmackPattern** m_pattern_list; int /*<<< orphan*/  is_nocase; } ;

/* Variables and functions */
 unsigned int SMACK_ANCHOR_BEGIN ; 
 unsigned int SMACK_ANCHOR_END ; 
 unsigned int SMACK_SNMP_HACK ; 
 unsigned int SMACK_WILDCARDS ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  free (struct SmackPattern**) ; 
 int /*<<< orphan*/  make_copy_of_pattern (unsigned char const*,unsigned int,int /*<<< orphan*/ ) ; 
 scalar_t__ malloc (int) ; 
 int /*<<< orphan*/  memcpy (struct SmackPattern**,struct SmackPattern**,int) ; 
 int /*<<< orphan*/  smack_add_symbols (struct SMACK*,unsigned char const*,int) ; 
 int /*<<< orphan*/  stderr ; 

void
smack_add_pattern(
    struct SMACK *  smack,
    const void *    v_pattern,
    unsigned        pattern_length,
    size_t          id,
    unsigned        flags)
{
    const unsigned char *pattern = (const unsigned char*)v_pattern;
    struct SmackPattern *pat;


    /*
     * Create a pattern structure based on the input
     */
    pat = (struct SmackPattern *)malloc(sizeof (struct SmackPattern));
    if (pat == NULL) {
        fprintf(stderr, "%s: out of memory error\n", "smack");
        exit(1);
    }
    pat->pattern_length = pattern_length;
    pat->is_anchor_begin = ((flags & SMACK_ANCHOR_BEGIN) > 0);
    pat->is_anchor_end = ((flags & SMACK_ANCHOR_END) > 0);
    pat->is_snmp_hack = ((flags & SMACK_SNMP_HACK) > 0);
    pat->is_wildcards = ((flags & SMACK_WILDCARDS) > 0);
    pat->id = id;
    pat->pattern = make_copy_of_pattern(pattern, pattern_length, smack->is_nocase);
    if (pat->is_anchor_begin)
        smack->is_anchor_begin = 1;
    if (pat->is_anchor_end)
        smack->is_anchor_end = 1;


    /*
     * Register the symbols used in the pattern. Hopefully, not all 256
     * possible combinations will be used, allowing us to shrink the
     * size of the rows in the final table
     */
    smack_add_symbols(smack, pattern, pattern_length);
    if (pat->is_snmp_hack)
        smack_add_symbols(smack, (const unsigned char *)"\x80", 1);


    /*
     * Automatically expand the table in order to hold more patterns,
     * as the caller keeps adding more.
     */
    if (smack->m_pattern_count + 1 >= smack->m_pattern_max) {
        struct SmackPattern **new_list;
        unsigned new_max;

        new_max = smack->m_pattern_max * 2 + 1;
        new_list = (struct SmackPattern **)malloc(sizeof(*new_list)*new_max);
        if (new_list == NULL) {
            fprintf(stderr, "%s: out of memory error\n", "smack");
            exit(1);
        }

        if (smack->m_pattern_list) {
            memcpy(    new_list,
                    smack->m_pattern_list,
                    sizeof(*new_list) * smack->m_pattern_count);
            free(smack->m_pattern_list);
        }

        smack->m_pattern_list = new_list;
        smack->m_pattern_max = new_max;
    }


    /*
     * Put this pattern onto the end of our list
     */
    smack->m_pattern_list[smack->m_pattern_count] = pat;
    smack->m_pattern_count++;
}