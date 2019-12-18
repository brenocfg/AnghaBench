#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int method_size; int types_size; } ;
struct TYPE_10__ {TYPE_2__ header; TYPE_1__* methods; scalar_t__ types; } ;
struct TYPE_8__ {int class_id; } ;
typedef  TYPE_3__ RBinDexObj ;

/* Variables and functions */
 char* dex_class_name_byid (TYPE_3__*,int) ; 
 char* dex_method_name (TYPE_3__*,int) ; 
 char* dex_method_signature (TYPE_3__*,int) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  r_return_val_if_fail (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  r_str_cpy (char*,char*) ; 
 char* r_str_newf (char*,char*,char const*,char*) ; 
 int /*<<< orphan*/  r_str_replace_char (char*,char,int /*<<< orphan*/ ) ; 
 scalar_t__ simplifiedDemangling ; 
 int /*<<< orphan*/  simplify (char*) ; 
 char* strchr (char*,char) ; 
 char* strdup (char const*) ; 

__attribute__((used)) static char *dex_method_fullname(RBinDexObj *bin, int method_idx) {
	r_return_val_if_fail (bin && bin->types, NULL);
	if (method_idx < 0 || method_idx >= bin->header.method_size) {
		return NULL;
	}
	int cid = bin->methods[method_idx].class_id;
	if (cid < 0 || cid >= bin->header.types_size) {
		return NULL;
	}
	const char *name = dex_method_name (bin, method_idx);
	if (!name) {
		return NULL;
	}
	const char *className = dex_class_name_byid (bin, cid);
	char *flagname = NULL;
	if (className) {
		char *class_name = strdup (className);
		r_str_replace_char (class_name, ';', 0);
		char *signature = dex_method_signature (bin, method_idx);
		if (signature) {
			flagname = r_str_newf ("%s.%s%s", class_name, name, signature);
			free (signature);
		} else {
			flagname = r_str_newf ("%s.%s%s", class_name, name, "???");
		}
		free (class_name);
	} else {
		char *signature = dex_method_signature (bin, method_idx);
		if (signature) {
			flagname = r_str_newf ("%s.%s%s", "???", name, signature);
			free (signature);
		} else {
			flagname = r_str_newf ("%s.%s%s", "???", name, "???");
			free (signature);
		}
	}
	if (flagname && simplifiedDemangling) {
		char *p = strchr (flagname, '(');
		if (p) {
			*p = 0;
			char *q = strchr (p + 1, ')');
			if (q) {
				simplify (q + 1);
				r_str_cpy (p, q + 1);
			}
			simplify (flagname);
		}
	}

	return flagname;
}