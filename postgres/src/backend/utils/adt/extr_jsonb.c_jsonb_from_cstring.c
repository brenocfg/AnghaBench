#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  state ;
typedef  int /*<<< orphan*/  sem ;
struct TYPE_5__ {int /*<<< orphan*/  res; int /*<<< orphan*/  object_field_start; int /*<<< orphan*/  scalar; int /*<<< orphan*/  array_end; int /*<<< orphan*/  object_end; int /*<<< orphan*/  array_start; int /*<<< orphan*/  object_start; void* semstate; } ;
typedef  TYPE_1__ JsonbInState ;
typedef  TYPE_1__ JsonSemAction ;
typedef  int /*<<< orphan*/  JsonLexContext ;
typedef  int /*<<< orphan*/  Datum ;

/* Variables and functions */
 int /*<<< orphan*/  JsonbValueToJsonb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PG_RETURN_POINTER (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jsonb_in_array_end ; 
 int /*<<< orphan*/  jsonb_in_array_start ; 
 int /*<<< orphan*/  jsonb_in_object_end ; 
 int /*<<< orphan*/  jsonb_in_object_field_start ; 
 int /*<<< orphan*/  jsonb_in_object_start ; 
 int /*<<< orphan*/  jsonb_in_scalar ; 
 int /*<<< orphan*/ * makeJsonLexContextCstringLen (char*,int,int) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pg_parse_json (int /*<<< orphan*/ *,TYPE_1__*) ; 

__attribute__((used)) static inline Datum
jsonb_from_cstring(char *json, int len)
{
	JsonLexContext *lex;
	JsonbInState state;
	JsonSemAction sem;

	memset(&state, 0, sizeof(state));
	memset(&sem, 0, sizeof(sem));
	lex = makeJsonLexContextCstringLen(json, len, true);

	sem.semstate = (void *) &state;

	sem.object_start = jsonb_in_object_start;
	sem.array_start = jsonb_in_array_start;
	sem.object_end = jsonb_in_object_end;
	sem.array_end = jsonb_in_array_end;
	sem.scalar = jsonb_in_scalar;
	sem.object_field_start = jsonb_in_object_field_start;

	pg_parse_json(lex, &sem);

	/* after parsing, the item member has the composed jsonb structure */
	PG_RETURN_POINTER(JsonbValueToJsonb(state.res));
}