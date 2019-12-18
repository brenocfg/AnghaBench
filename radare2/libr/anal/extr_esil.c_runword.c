#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {scalar_t__ (* hook_command ) (TYPE_4__*,char const*) ;} ;
struct TYPE_16__ {int parse_goto_count; int trap; int parse_stop; int skip; int trap_code; scalar_t__ verbose; int /*<<< orphan*/ * current_opstr; TYPE_2__ cb; TYPE_1__* Reil; } ;
struct TYPE_15__ {int (* code ) (TYPE_4__*) ;} ;
struct TYPE_13__ {int skip; char* if_buf; scalar_t__ cmd_count; scalar_t__ addr; } ;
typedef  TYPE_3__ RAnalEsilOp ;
typedef  TYPE_4__ RAnalEsil ;

/* Variables and functions */
 int /*<<< orphan*/  ERR (char*) ; 
 int /*<<< orphan*/  eprintf (char*,char const*) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 scalar_t__ iscommand (TYPE_4__*,char const*,TYPE_3__**) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  r_anal_esil_parse (TYPE_4__*,char*) ; 
 int /*<<< orphan*/  r_anal_esil_push (TYPE_4__*,char const*) ; 
 int /*<<< orphan*/  r_anal_esil_pushnum (TYPE_4__*,scalar_t__) ; 
 scalar_t__ strcmp (char const*,char*) ; 
 int /*<<< orphan*/ * strdup (char const*) ; 
 int strlen (char*) ; 
 int /*<<< orphan*/  strncat (char*,char const*,int) ; 
 scalar_t__ stub1 (TYPE_4__*,char const*) ; 
 int stub2 (TYPE_4__*) ; 

__attribute__((used)) static int runword(RAnalEsil *esil, const char *word) {
	RAnalEsilOp *op = NULL;
	if (!word) {
		return 0;
	}
	esil->parse_goto_count--;
	if (esil->parse_goto_count < 1) {
		ERR ("ESIL infinite loop detected\n");
		esil->trap = 1;       // INTERNAL ERROR
		esil->parse_stop = 1; // INTERNAL ERROR
		return 0;
	}

	// Don't push anything onto stack when processing if statements
	if (!strcmp (word, "?{") && esil->Reil) {
		esil->Reil->skip = esil->Reil->skip? 0: 1;
		if (esil->Reil->skip) {
			esil->Reil->cmd_count = 0;
			memset (esil->Reil->if_buf, 0, sizeof (esil->Reil->if_buf));
		}
	}

	if (esil->Reil && esil->Reil->skip) {
		char *if_buf = esil->Reil->if_buf;
		strncat (if_buf, word, sizeof (esil->Reil->if_buf) - strlen (if_buf) - 1);
		strncat (if_buf, ",", sizeof (esil->Reil->if_buf) - strlen (if_buf) - 1);
		if (!strcmp (word, "}")) {
			r_anal_esil_pushnum (esil, esil->Reil->addr + esil->Reil->cmd_count + 1);
			r_anal_esil_parse (esil, esil->Reil->if_buf);
			return 1;
		}
		if (iscommand (esil, word, &op)) {
			esil->Reil->cmd_count++;
		}
		return 1;
	}

	//eprintf ("WORD (%d) (%s)\n", esil->skip, word);
	if (!strcmp (word, "}{")) {
		if (esil->skip == 1) {
			esil->skip = 0;
		} else if (esil->skip == 0) {	//this isn't perfect, but should work for valid esil
			esil->skip = 1;
		}
		return 1;
	} else if (!strcmp (word, "}")) {
		if (esil->skip) {
			esil->skip--;
		}
		return 1;
	}
	if (esil->skip && strcmp(word, "?{")) {
		return 1;
	}

	if (iscommand (esil, word, &op)) {
		// run action
		if (op) {
			if (esil->cb.hook_command) {
				if (esil->cb.hook_command (esil, word)) {
					return 1; // XXX cannot return != 1
				}
			}
			esil->current_opstr = strdup (word);
			//so this is basically just sharing what's the operation with the operation
			//useful for wrappers
			const bool ret = op->code (esil);
			free (esil->current_opstr);
			esil->current_opstr = NULL;
			if (!ret) {
				if (esil->verbose) {
					eprintf ("%s returned 0\n", word);
				}
			}
			return ret;
		}
	}
	if (!*word || *word == ',') {
		// skip empty words
		return 1;
	}

	// push value
	if (!r_anal_esil_push (esil, word)) {
		ERR ("ESIL stack is full");
		esil->trap = 1;
		esil->trap_code = 1;
	}
	return 1;
}