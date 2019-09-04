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
struct lexer {int dummy; } ;
struct config_data {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  sections; int /*<<< orphan*/ * file; } ;
typedef  TYPE_1__ config_t ;

/* Variables and functions */
 int CONFIG_ERROR ; 
 int CONFIG_SUCCESS ; 
 int /*<<< orphan*/  bfree (TYPE_1__*) ; 
 TYPE_1__* bzalloc (int) ; 
 int /*<<< orphan*/  init_mutex (TYPE_1__*) ; 
 int /*<<< orphan*/  lexer_free (struct lexer*) ; 
 int /*<<< orphan*/  lexer_init (struct lexer*) ; 
 int /*<<< orphan*/  lexer_start (struct lexer*,char const*) ; 
 int /*<<< orphan*/  parse_config_data (int /*<<< orphan*/ *,struct lexer*) ; 

int config_open_string(config_t **config, const char *str)
{
	struct lexer lex;

	if (!config)
		return CONFIG_ERROR;

	*config = bzalloc(sizeof(struct config_data));
	if (!*config)
		return CONFIG_ERROR;

	if (!init_mutex(*config)) {
		bfree(*config);
		return CONFIG_ERROR;
	}

	(*config)->file = NULL;

	lexer_init(&lex);
	lexer_start(&lex, str);
	parse_config_data(&(*config)->sections, &lex);
	lexer_free(&lex);

	return CONFIG_SUCCESS;
}