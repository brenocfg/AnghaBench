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
typedef  scalar_t__ transition_t ;
struct SMACK {unsigned int m_state_count; unsigned char* char_to_symbol; int row_shift; scalar_t__* table; int /*<<< orphan*/  symbol_count; } ;

/* Variables and functions */
 unsigned int ALPHABET_SIZE ; 
 unsigned int GOTO (unsigned int,unsigned int) ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 scalar_t__* malloc (int) ; 
 int /*<<< orphan*/  memset (scalar_t__*,int /*<<< orphan*/ ,int) ; 
 int row_shift_from_symbol_count (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static void
smack_stage4_make_final_table(struct SMACK *smack)
{
    unsigned row;
    unsigned row_count = smack->m_state_count;
    unsigned column_count;
    transition_t *table;
    unsigned char *char_to_symbol = smack->char_to_symbol;

    /*
     * Figure out the row-size-shift. Instead of doing a multiply by the
     * row-width, we expand it out to the nearest pattern of two, and
     * then use shifts instead of multiplies.
     */
    smack->row_shift = row_shift_from_symbol_count(smack->symbol_count);
    column_count = 1 << smack->row_shift;

    /*
     * Allocate table:
     * rows*columns
     */
    table = malloc(sizeof(transition_t) * row_count * column_count);
    if (table == NULL) {
        fprintf(stderr, "%s: out of memory error\n", "smack");
        exit(1);
    }
    memset(table, 0, sizeof(transition_t) * row_count * column_count);


    for (row=0; row<row_count; row++) {
        unsigned col;

        for (col=0; col<ALPHABET_SIZE; col++) {
            unsigned transition;
            unsigned symbol = char_to_symbol[col];

            transition = GOTO(row,col);

            *(table + row*column_count + symbol) = (transition_t)transition;
        }
    }

    smack->table = table;
}