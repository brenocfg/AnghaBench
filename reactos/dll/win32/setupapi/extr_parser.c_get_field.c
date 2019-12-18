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
struct line {int key_field; int nb_fields; int first_field; } ;
struct inf_file {struct field* fields; } ;
struct field {int dummy; } ;

/* Variables and functions */
 struct line* get_line (struct inf_file*,int,int) ; 

__attribute__((used)) static struct field *get_field( struct inf_file *file, int section_index, int line_index,
                                int field_index )
{
    struct line *line = get_line( file, section_index, line_index );

    if (!line) return NULL;
    if (!field_index)  /* get the key */
    {
        if (line->key_field == -1) return NULL;
        return &file->fields[line->key_field];
    }
    field_index--;
    if (field_index >= line->nb_fields) return NULL;
    return &file->fields[line->first_field + field_index];
}