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
typedef  int /*<<< orphan*/  yaml_event_t ;
typedef  int /*<<< orphan*/  yaml_emitter_t ;
typedef  int /*<<< orphan*/  yaml_char_t ;
struct dt_info {int /*<<< orphan*/  dt; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  YAML_ANY_SEQUENCE_STYLE ; 
 scalar_t__ YAML_SEQ_TAG ; 
 int /*<<< orphan*/  YAML_UTF8_ENCODING ; 
 int /*<<< orphan*/  yaml_document_end_event_initialize (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  yaml_document_start_event_initialize (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  yaml_emitter_delete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  yaml_emitter_emit_or_die (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  yaml_emitter_initialize (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  yaml_emitter_set_output_file (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  yaml_sequence_end_event_initialize (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  yaml_sequence_start_event_initialize (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  yaml_stream_end_event_initialize (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  yaml_stream_start_event_initialize (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  yaml_tree (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void dt_to_yaml(FILE *f, struct dt_info *dti)
{
	yaml_emitter_t emitter;
	yaml_event_t event;

	yaml_emitter_initialize(&emitter);
	yaml_emitter_set_output_file(&emitter, f);
	yaml_stream_start_event_initialize(&event, YAML_UTF8_ENCODING);
	yaml_emitter_emit_or_die(&emitter, &event);

	yaml_document_start_event_initialize(&event, NULL, NULL, NULL, 0);
	yaml_emitter_emit_or_die(&emitter, &event);

	yaml_sequence_start_event_initialize(&event, NULL, (yaml_char_t *)YAML_SEQ_TAG, 1, YAML_ANY_SEQUENCE_STYLE);
	yaml_emitter_emit_or_die(&emitter, &event);

	yaml_tree(dti->dt, &emitter);

	yaml_sequence_end_event_initialize(&event);
	yaml_emitter_emit_or_die(&emitter, &event);

	yaml_document_end_event_initialize(&event, 0);
	yaml_emitter_emit_or_die(&emitter, &event);

	yaml_stream_end_event_initialize(&event);
	yaml_emitter_emit_or_die(&emitter, &event);

	yaml_emitter_delete(&emitter);
}