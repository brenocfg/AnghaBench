#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  mpc_state_t ;
struct TYPE_3__ {int backtrack; int marks_slots; char last; int /*<<< orphan*/  mem_full; scalar_t__ mem_index; void* lasts; void* marks; scalar_t__ marks_num; scalar_t__ suppress; int /*<<< orphan*/ * file; int /*<<< orphan*/ * buffer; void* string; int /*<<< orphan*/  state; int /*<<< orphan*/  type; void* filename; } ;
typedef  TYPE_1__ mpc_input_t ;

/* Variables and functions */
 int MPC_INPUT_MARKS_MIN ; 
 int MPC_INPUT_MEM_NUM ; 
 int /*<<< orphan*/  MPC_INPUT_STRING ; 
 void* malloc (int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mpc_state_new () ; 
 int /*<<< orphan*/  strcpy (void*,char const*) ; 
 int strlen (char const*) ; 

__attribute__((used)) static mpc_input_t *mpc_input_new_string(const char *filename, const char *string) {

  mpc_input_t *i = malloc(sizeof(mpc_input_t));
  
  i->filename = malloc(strlen(filename) + 1);
  strcpy(i->filename, filename);
  i->type = MPC_INPUT_STRING;
  
  i->state = mpc_state_new();
  
  i->string = malloc(strlen(string) + 1);
  strcpy(i->string, string);
  i->buffer = NULL;
  i->file = NULL;
  
  i->suppress = 0;
  i->backtrack = 1;
  i->marks_num = 0;
  i->marks_slots = MPC_INPUT_MARKS_MIN;
  i->marks = malloc(sizeof(mpc_state_t) * i->marks_slots);
  i->lasts = malloc(sizeof(char) * i->marks_slots);
  i->last = '\0';
  
  i->mem_index = 0;
  memset(i->mem_full, 0, sizeof(char) * MPC_INPUT_MEM_NUM);
  
  return i;
}