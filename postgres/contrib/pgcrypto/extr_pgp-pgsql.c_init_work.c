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
typedef  int /*<<< orphan*/  uint8 ;
typedef  int /*<<< orphan*/  text ;
struct debug_expect {scalar_t__ debug; } ;
typedef  int /*<<< orphan*/  PGP_Context ;

/* Variables and functions */
 scalar_t__ VARDATA_ANY (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  VARSIZE_ANY_EXHDR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fill_expect (struct debug_expect*,int) ; 
 int parse_args (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct debug_expect*) ; 
 int pgp_init (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  pgp_set_text_mode (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  px_THROW_ERROR (int) ; 
 int /*<<< orphan*/  px_set_debug_handler (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  show_debug ; 

__attribute__((used)) static void
init_work(PGP_Context **ctx_p, int is_text,
		  text *args, struct debug_expect *ex)
{
	int			err = pgp_init(ctx_p);

	fill_expect(ex, is_text);

	if (err == 0 && args != NULL)
		err = parse_args(*ctx_p, (uint8 *) VARDATA_ANY(args),
						 VARSIZE_ANY_EXHDR(args), ex);

	if (err)
		px_THROW_ERROR(err);

	if (ex->debug)
		px_set_debug_handler(show_debug);

	pgp_set_text_mode(*ctx_p, is_text);
}