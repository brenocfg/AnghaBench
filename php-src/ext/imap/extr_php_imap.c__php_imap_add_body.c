#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zval ;
struct TYPE_8__ {TYPE_4__* parameter; scalar_t__ type; } ;
struct TYPE_7__ {int lines; int bytes; } ;
struct TYPE_11__ {scalar_t__ type; scalar_t__ encoding; struct TYPE_11__* CONTENT_MSG_BODY; scalar_t__ subtype; TYPE_3__* CONTENT_PART; TYPE_4__* parameter; TYPE_2__ disposition; TYPE_1__ size; scalar_t__ id; scalar_t__ description; } ;
struct TYPE_10__ {scalar_t__ value; scalar_t__ attribute; struct TYPE_10__* next; } ;
struct TYPE_9__ {TYPE_5__ body; struct TYPE_9__* next; } ;
typedef  TYPE_3__ PART ;
typedef  TYPE_4__ PARAMETER ;
typedef  TYPE_5__ BODY ;

/* Variables and functions */
 scalar_t__ ENCMAX ; 
 scalar_t__ TYPEMAX ; 
 scalar_t__ TYPEMESSAGE ; 
 scalar_t__ TYPEMULTIPART ; 
 int /*<<< orphan*/  add_assoc_object (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  add_next_index_object (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  add_property_long (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  add_property_string (int /*<<< orphan*/ *,char*,scalar_t__) ; 
 int /*<<< orphan*/  array_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  object_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strcasecmp (scalar_t__,char*) ; 

void _php_imap_add_body(zval *arg, BODY *body)
{
	zval parametres, param, dparametres, dparam;
	PARAMETER *par, *dpar;
	PART *part;

	if (body->type <= TYPEMAX) {
		add_property_long(arg, "type", body->type);
	}

	if (body->encoding <= ENCMAX) {
		add_property_long(arg, "encoding", body->encoding);
	}

	if (body->subtype) {
		add_property_long(arg, "ifsubtype", 1);
		add_property_string(arg, "subtype", body->subtype);
	} else {
		add_property_long(arg, "ifsubtype", 0);
	}

	if (body->description) {
		add_property_long(arg, "ifdescription", 1);
		add_property_string(arg, "description", body->description);
	} else {
		add_property_long(arg, "ifdescription", 0);
	}

	if (body->id) {
		add_property_long(arg, "ifid", 1);
		add_property_string(arg, "id", body->id);
	} else {
		add_property_long(arg, "ifid", 0);
	}

	if (body->size.lines) {
		add_property_long(arg, "lines", body->size.lines);
	}

	if (body->size.bytes) {
		add_property_long(arg, "bytes", body->size.bytes);
	}

#ifdef IMAP41
	if (body->disposition.type) {
		add_property_long(arg, "ifdisposition", 1);
		add_property_string(arg, "disposition", body->disposition.type);
	} else {
		add_property_long(arg, "ifdisposition", 0);
	}

	if (body->disposition.parameter) {
		dpar = body->disposition.parameter;
		add_property_long(arg, "ifdparameters", 1);
		array_init(&dparametres);
		do {
			object_init(&dparam);
			add_property_string(&dparam, "attribute", dpar->attribute);
			add_property_string(&dparam, "value", dpar->value);
			add_next_index_object(&dparametres, &dparam);
		} while ((dpar = dpar->next));
		add_assoc_object(arg, "dparameters", &dparametres);
	} else {
		add_property_long(arg, "ifdparameters", 0);
	}
#endif

	if ((par = body->parameter)) {
		add_property_long(arg, "ifparameters", 1);

		array_init(&parametres);
		do {
			object_init(&param);
			if (par->attribute) {
				add_property_string(&param, "attribute", par->attribute);
			}
			if (par->value) {
				add_property_string(&param, "value", par->value);
			}

			add_next_index_object(&parametres, &param);
		} while ((par = par->next));
	} else {
		object_init(&parametres);
		add_property_long(arg, "ifparameters", 0);
	}
	add_assoc_object(arg, "parameters", &parametres);

	/* multipart message ? */
	if (body->type == TYPEMULTIPART) {
		array_init(&parametres);
		for (part = body->CONTENT_PART; part; part = part->next) {
			object_init(&param);
			_php_imap_add_body(&param, &part->body);
			add_next_index_object(&parametres, &param);
		}
		add_assoc_object(arg, "parts", &parametres);
	}

	/* encapsulated message ? */
	if ((body->type == TYPEMESSAGE) && (!strcasecmp(body->subtype, "rfc822"))) {
		body = body->CONTENT_MSG_BODY;
		array_init(&parametres);
		object_init(&param);
		_php_imap_add_body(&param, body);
		add_next_index_object(&parametres, &param);
		add_assoc_object(arg, "parts", &parametres);
	}
}