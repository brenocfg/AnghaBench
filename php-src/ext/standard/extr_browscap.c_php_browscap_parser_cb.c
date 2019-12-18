#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zval ;
typedef  int /*<<< orphan*/  zend_string ;
struct TYPE_9__ {int /*<<< orphan*/  kv_used; int /*<<< orphan*/  htab; } ;
typedef  TYPE_1__ browser_data ;
struct TYPE_10__ {int /*<<< orphan*/ * current_section_name; TYPE_3__* current_entry; TYPE_1__* bdata; } ;
typedef  TYPE_2__ browscap_parser_ctx ;
struct TYPE_11__ {size_t prefix_len; int /*<<< orphan*/ * contains_len; int /*<<< orphan*/ * contains_start; int /*<<< orphan*/ * parent; int /*<<< orphan*/  kv_start; int /*<<< orphan*/  kv_end; void* pattern; } ;
typedef  TYPE_3__ browscap_entry ;
typedef  int /*<<< orphan*/  Z_TYPE_FLAGS_P ;

/* Variables and functions */
 int BROWSCAP_NUM_CONTAINS ; 
 int /*<<< orphan*/  E_CORE_ERROR ; 
 int /*<<< orphan*/  E_WARNING ; 
 int GC_FLAGS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INI_STR (char*) ; 
 int IS_ARRAY_PERSISTENT ; 
 int /*<<< orphan*/  UINT16_MAX ; 
#define  ZEND_INI_PARSER_ENTRY 129 
#define  ZEND_INI_PARSER_SECTION 128 
 int /*<<< orphan*/ * ZSTR_CHAR (char) ; 
 int /*<<< orphan*/ * ZSTR_EMPTY_ALLOC () ; 
 int /*<<< orphan*/  ZSTR_IS_INTERNED (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ZSTR_LEN (int /*<<< orphan*/ *) ; 
 char* ZSTR_VAL (int /*<<< orphan*/ *) ; 
 int Z_STRLEN_P (int /*<<< orphan*/ *) ; 
 char* Z_STRVAL_P (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * Z_STR_P (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  browscap_add_kv (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 size_t browscap_compute_contains (int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 size_t browscap_compute_prefix_len (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * browscap_intern_str (TYPE_2__*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * browscap_intern_str_ci (TYPE_2__*,int /*<<< orphan*/ *,int) ; 
 TYPE_3__* pemalloc (int,int) ; 
 int /*<<< orphan*/  php_error_docref (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcasecmp (char*,char*) ; 
 int /*<<< orphan*/  strncasecmp (char*,char*,int) ; 
 int /*<<< orphan*/  zend_error (int /*<<< orphan*/ ,char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zend_hash_update_ptr (int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_3__*) ; 
 int /*<<< orphan*/ * zend_new_interned_string (void*) ; 
 void* zend_string_copy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zend_string_release (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void php_browscap_parser_cb(zval *arg1, zval *arg2, zval *arg3, int callback_type, void *arg) /* {{{ */
{
	browscap_parser_ctx *ctx = arg;
	browser_data *bdata = ctx->bdata;
	int persistent = GC_FLAGS(bdata->htab) & IS_ARRAY_PERSISTENT;

	if (!arg1) {
		return;
	}

	switch (callback_type) {
		case ZEND_INI_PARSER_ENTRY:
			if (ctx->current_entry != NULL && arg2) {
				zend_string *new_key, *new_value;

				/* Set proper value for true/false settings */
				if ((Z_STRLEN_P(arg2) == 2 && !strncasecmp(Z_STRVAL_P(arg2), "on", sizeof("on") - 1)) ||
					(Z_STRLEN_P(arg2) == 3 && !strncasecmp(Z_STRVAL_P(arg2), "yes", sizeof("yes") - 1)) ||
					(Z_STRLEN_P(arg2) == 4 && !strncasecmp(Z_STRVAL_P(arg2), "true", sizeof("true") - 1))
				) {
					new_value = ZSTR_CHAR('1');
				} else if (
					(Z_STRLEN_P(arg2) == 2 && !strncasecmp(Z_STRVAL_P(arg2), "no", sizeof("no") - 1)) ||
					(Z_STRLEN_P(arg2) == 3 && !strncasecmp(Z_STRVAL_P(arg2), "off", sizeof("off") - 1)) ||
					(Z_STRLEN_P(arg2) == 4 && !strncasecmp(Z_STRVAL_P(arg2), "none", sizeof("none") - 1)) ||
					(Z_STRLEN_P(arg2) == 5 && !strncasecmp(Z_STRVAL_P(arg2), "false", sizeof("false") - 1))
				) {
					new_value = ZSTR_EMPTY_ALLOC();
				} else { /* Other than true/false setting */
					new_value = browscap_intern_str(ctx, Z_STR_P(arg2), persistent);
				}

				if (!strcasecmp(Z_STRVAL_P(arg1), "parent")) {
					/* parent entry can not be same as current section -> causes infinite loop! */
					if (ctx->current_section_name != NULL &&
						!strcasecmp(ZSTR_VAL(ctx->current_section_name), Z_STRVAL_P(arg2))
					) {
						zend_error(E_CORE_ERROR, "Invalid browscap ini file: "
							"'Parent' value cannot be same as the section name: %s "
							"(in file %s)", ZSTR_VAL(ctx->current_section_name), INI_STR("browscap"));
						return;
					}

					if (ctx->current_entry->parent) {
						zend_string_release(ctx->current_entry->parent);
					}

					ctx->current_entry->parent = new_value;
				} else {
					new_key = browscap_intern_str_ci(ctx, Z_STR_P(arg1), persistent);
					browscap_add_kv(bdata, new_key, new_value, persistent);
					ctx->current_entry->kv_end = bdata->kv_used;
				}
			}
			break;
		case ZEND_INI_PARSER_SECTION:
		{
			browscap_entry *entry;
			zend_string *pattern = Z_STR_P(arg1);
			size_t pos;
			int i;

			if (ZSTR_LEN(pattern) > UINT16_MAX) {
				php_error_docref(NULL, E_WARNING,
					"Skipping excessively long pattern of length %zd", ZSTR_LEN(pattern));
				break;
			}

			if (persistent) {
				pattern = zend_new_interned_string(zend_string_copy(pattern));
				if (ZSTR_IS_INTERNED(pattern)) {
					Z_TYPE_FLAGS_P(arg1) = 0;
				} else {
					zend_string_release(pattern);
				}
			}

			entry = ctx->current_entry
				= pemalloc(sizeof(browscap_entry), persistent);
			zend_hash_update_ptr(bdata->htab, pattern, entry);

			if (ctx->current_section_name) {
				zend_string_release(ctx->current_section_name);
			}
			ctx->current_section_name = zend_string_copy(pattern);

			entry->pattern = zend_string_copy(pattern);
			entry->kv_end = entry->kv_start = bdata->kv_used;
			entry->parent = NULL;

			pos = entry->prefix_len = browscap_compute_prefix_len(pattern);
			for (i = 0; i < BROWSCAP_NUM_CONTAINS; i++) {
				pos = browscap_compute_contains(pattern, pos,
					&entry->contains_start[i], &entry->contains_len[i]);
			}
			break;
		}
	}
}