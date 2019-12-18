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
struct ep_param {char* type; char* name; int is_property; int is_const; int is_uniform; int is_texture; int written; int writeorder; int /*<<< orphan*/  annotations; int /*<<< orphan*/  properties; int /*<<< orphan*/  default_val; scalar_t__ array_count; } ;

/* Variables and functions */
 scalar_t__ astrcmp_n (char*,char*,int) ; 
 int /*<<< orphan*/  da_init (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void ep_param_init(struct ep_param *epp, char *type, char *name,
				 bool is_property, bool is_const,
				 bool is_uniform)
{
	epp->type = type;
	epp->name = name;
	epp->is_property = is_property;
	epp->is_const = is_const;
	epp->is_uniform = is_uniform;
	epp->is_texture = (astrcmp_n(epp->type, "texture", 7) == 0);
	epp->written = false;
	epp->writeorder = false;
	epp->array_count = 0;
	da_init(epp->default_val);
	da_init(epp->properties);
	da_init(epp->annotations);
}