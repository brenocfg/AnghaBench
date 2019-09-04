#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {char* ident; char* name; int /*<<< orphan*/ * grammar; } ;
typedef  TYPE_1__ mpca_stmt_t ;
typedef  TYPE_1__ mpc_val_t ;
typedef  int /*<<< orphan*/  mpc_parser_t ;

/* Variables and functions */
 int /*<<< orphan*/  free (char*) ; 
 TYPE_1__* malloc (int) ; 

__attribute__((used)) static mpc_val_t *mpca_stmt_afold(int n, mpc_val_t **xs) {
  mpca_stmt_t *stmt = malloc(sizeof(mpca_stmt_t));
  stmt->ident = ((char**)xs)[0];
  stmt->name = ((char**)xs)[1];
  stmt->grammar = ((mpc_parser_t**)xs)[3];
  (void) n;
  free(((char**)xs)[2]);
  free(((char**)xs)[4]);
  
  return stmt;
}