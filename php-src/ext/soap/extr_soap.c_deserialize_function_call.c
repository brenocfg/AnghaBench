#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_44__   TYPE_9__ ;
typedef  struct TYPE_43__   TYPE_8__ ;
typedef  struct TYPE_42__   TYPE_7__ ;
typedef  struct TYPE_41__   TYPE_6__ ;
typedef  struct TYPE_40__   TYPE_5__ ;
typedef  struct TYPE_39__   TYPE_4__ ;
typedef  struct TYPE_38__   TYPE_3__ ;
typedef  struct TYPE_37__   TYPE_2__ ;
typedef  struct TYPE_36__   TYPE_1__ ;
typedef  struct TYPE_35__   TYPE_12__ ;
typedef  struct TYPE_34__   TYPE_11__ ;
typedef  struct TYPE_33__   TYPE_10__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zval ;
typedef  TYPE_5__* xmlNodePtr ;
typedef  TYPE_6__* xmlDocPtr ;
typedef  TYPE_7__* xmlAttrPtr ;
struct TYPE_43__ {int mustUnderstand; int num_params; struct TYPE_43__* next; int /*<<< orphan*/  retval; int /*<<< orphan*/ * parameters; TYPE_12__* function; TYPE_11__* hdr; int /*<<< orphan*/  function_name; } ;
typedef  TYPE_8__ soapHeader ;
struct TYPE_44__ {int /*<<< orphan*/  s; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_9__ smart_str ;
typedef  TYPE_10__* sdlSoapBindingFunctionPtr ;
typedef  TYPE_11__* sdlSoapBindingFunctionHeaderPtr ;
typedef  int /*<<< orphan*/ * sdlPtr ;
typedef  TYPE_12__* sdlFunctionPtr ;
struct TYPE_42__ {TYPE_1__* children; struct TYPE_42__* next; int /*<<< orphan*/ * ns; } ;
struct TYPE_41__ {int /*<<< orphan*/  children; } ;
struct TYPE_40__ {scalar_t__ type; struct TYPE_40__* children; struct TYPE_40__* next; TYPE_2__* ns; TYPE_7__* properties; int /*<<< orphan*/  name; } ;
struct TYPE_39__ {scalar_t__ bindingType; } ;
struct TYPE_38__ {scalar_t__ headers; } ;
struct TYPE_37__ {scalar_t__ href; } ;
struct TYPE_36__ {scalar_t__ content; } ;
struct TYPE_35__ {int /*<<< orphan*/  bindingAttributes; TYPE_4__* binding; scalar_t__ functionName; } ;
struct TYPE_34__ {int /*<<< orphan*/  encode; } ;
struct TYPE_33__ {scalar_t__ style; TYPE_3__ input; } ;

/* Variables and functions */
 scalar_t__ BINDING_SOAP ; 
 int /*<<< orphan*/  E_ERROR ; 
 int SOAP_1_1 ; 
 char* SOAP_1_1_ACTOR_NEXT ; 
 char* SOAP_1_1_ENC_NAMESPACE ; 
 char* SOAP_1_1_ENV_NAMESPACE ; 
 int SOAP_1_2 ; 
 char* SOAP_1_2_ACTOR_NEXT ; 
 char* SOAP_1_2_ACTOR_UNLIMATERECEIVER ; 
 char* SOAP_1_2_ENC_NAMESPACE ; 
 char* SOAP_1_2_ENV_NAMESPACE ; 
 scalar_t__ SOAP_RPC ; 
 scalar_t__ XML_ELEMENT_NODE ; 
 int /*<<< orphan*/  ZVAL_NULL (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ZVAL_STRING (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  Z_STRLEN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Z_STRVAL (int /*<<< orphan*/ ) ; 
 scalar_t__ attr_is_equal_ex (TYPE_7__*,char*,char*) ; 
 int /*<<< orphan*/  deserialize_parameters (TYPE_5__*,TYPE_12__*,int*,int /*<<< orphan*/ **) ; 
 void* emalloc (int) ; 
 int /*<<< orphan*/  encode_finish () ; 
 int /*<<< orphan*/  encode_reset_ns () ; 
 void* find_function (int /*<<< orphan*/ *,TYPE_5__*,int /*<<< orphan*/ *) ; 
 TYPE_7__* get_attribute_ex (TYPE_7__*,char*,char*) ; 
 TYPE_12__* get_doc_function (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_5__* get_envelope (int /*<<< orphan*/ ,int*,char**) ; 
 int /*<<< orphan*/  master_to_zval (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_5__*) ; 
 int /*<<< orphan*/  memset (TYPE_8__*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ node_is_equal_ex (TYPE_5__*,char*,char*) ; 
 int /*<<< orphan*/  php_error (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smart_str_0 (TYPE_9__*) ; 
 int /*<<< orphan*/  smart_str_appendc (TYPE_9__*,char) ; 
 int /*<<< orphan*/  smart_str_appendl (TYPE_9__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smart_str_appends (TYPE_9__*,char*) ; 
 int /*<<< orphan*/  smart_str_free (TYPE_9__*) ; 
 int /*<<< orphan*/  soap_server_fault (char*,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ strcmp (char*,char*) ; 
 TYPE_11__* zend_hash_find_ptr (scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static sdlFunctionPtr deserialize_function_call(sdlPtr sdl, xmlDocPtr request, char* actor, zval *function_name, int *num_params, zval **parameters, int *version, soapHeader **headers) /* {{{ */
{
	char* envelope_ns = NULL;
	xmlNodePtr trav,env,head,body,func;
	xmlAttrPtr attr;
	sdlFunctionPtr function;

	encode_reset_ns();

	/* Get <Envelope> element */
	env = get_envelope(request->children, version, &envelope_ns);
	if (!env) {
		soap_server_fault("Client", "looks like we got XML without \"Envelope\" element", NULL, NULL, NULL);
	}

	attr = env->properties;
	while (attr != NULL) {
		if (attr->ns == NULL) {
			soap_server_fault("Client", "A SOAP Envelope element cannot have non Namespace qualified attributes", NULL, NULL, NULL);
		} else if (attr_is_equal_ex(attr,"encodingStyle",SOAP_1_2_ENV_NAMESPACE)) {
			if (*version == SOAP_1_2) {
				soap_server_fault("Client", "encodingStyle cannot be specified on the Envelope", NULL, NULL, NULL);
			} else if (strcmp((char*)attr->children->content,SOAP_1_1_ENC_NAMESPACE) != 0) {
				soap_server_fault("Client", "Unknown data encoding style", NULL, NULL, NULL);
			}
		}
		attr = attr->next;
	}

	/* Get <Header> element */
	head = NULL;
	trav = env->children;
	while (trav != NULL && trav->type != XML_ELEMENT_NODE) {
		trav = trav->next;
	}
	if (trav != NULL && node_is_equal_ex(trav,"Header",envelope_ns)) {
		head = trav;
		trav = trav->next;
	}

	/* Get <Body> element */
	body = NULL;
	while (trav != NULL && trav->type != XML_ELEMENT_NODE) {
		trav = trav->next;
	}
	if (trav != NULL && node_is_equal_ex(trav,"Body",envelope_ns)) {
		body = trav;
		trav = trav->next;
	}
	while (trav != NULL && trav->type != XML_ELEMENT_NODE) {
		trav = trav->next;
	}
	if (body == NULL) {
		soap_server_fault("Client", "Body must be present in a SOAP envelope", NULL, NULL, NULL);
	}
	attr = body->properties;
	while (attr != NULL) {
		if (attr->ns == NULL) {
			if (*version == SOAP_1_2) {
				soap_server_fault("Client", "A SOAP Body element cannot have non Namespace qualified attributes", NULL, NULL, NULL);
			}
		} else if (attr_is_equal_ex(attr,"encodingStyle",SOAP_1_2_ENV_NAMESPACE)) {
			if (*version == SOAP_1_2) {
				soap_server_fault("Client", "encodingStyle cannot be specified on the Body", NULL, NULL, NULL);
			} else if (strcmp((char*)attr->children->content,SOAP_1_1_ENC_NAMESPACE) != 0) {
				soap_server_fault("Client", "Unknown data encoding style", NULL, NULL, NULL);
			}
		}
		attr = attr->next;
	}

	if (trav != NULL && *version == SOAP_1_2) {
		soap_server_fault("Client", "A SOAP 1.2 envelope can contain only Header and Body", NULL, NULL, NULL);
	}

	func = NULL;
	trav = body->children;
	while (trav != NULL) {
		if (trav->type == XML_ELEMENT_NODE) {
/*
			if (func != NULL) {
				soap_server_fault("Client", "looks like we got \"Body\" with several functions call", NULL, NULL, NULL);
			}
*/
			func = trav;
			break; /* FIXME: the rest of body is ignored */
		}
		trav = trav->next;
	}
	if (func == NULL) {
		function = get_doc_function(sdl, NULL);
		if (function != NULL) {
			ZVAL_STRING(function_name, (char *)function->functionName);
		} else {
			soap_server_fault("Client", "looks like we got \"Body\" without function call", NULL, NULL, NULL);
		}
	} else {
		if (*version == SOAP_1_1) {
			attr = get_attribute_ex(func->properties,"encodingStyle",SOAP_1_1_ENV_NAMESPACE);
			if (attr && strcmp((char*)attr->children->content,SOAP_1_1_ENC_NAMESPACE) != 0) {
				soap_server_fault("Client","Unknown Data Encoding Style", NULL, NULL, NULL);
			}
		} else {
			attr = get_attribute_ex(func->properties,"encodingStyle",SOAP_1_2_ENV_NAMESPACE);
			if (attr && strcmp((char*)attr->children->content,SOAP_1_2_ENC_NAMESPACE) != 0) {
				soap_server_fault("DataEncodingUnknown","Unknown Data Encoding Style", NULL, NULL, NULL);
			}
		}
		function = find_function(sdl, func, function_name);
		if (sdl != NULL && function == NULL) {
			if (*version == SOAP_1_2) {
				soap_server_fault("rpc:ProcedureNotPresent","Procedure not present", NULL, NULL, NULL);
			} else {
				php_error(E_ERROR, "Procedure '%s' not present", func->name);
			}
		}
	}

	*headers = NULL;
	if (head) {
		soapHeader *h, *last = NULL;

		attr = head->properties;
		while (attr != NULL) {
			if (attr->ns == NULL) {
				soap_server_fault("Client", "A SOAP Header element cannot have non Namespace qualified attributes", NULL, NULL, NULL);
			} else if (attr_is_equal_ex(attr,"encodingStyle",SOAP_1_2_ENV_NAMESPACE)) {
				if (*version == SOAP_1_2) {
					soap_server_fault("Client", "encodingStyle cannot be specified on the Header", NULL, NULL, NULL);
				} else if (strcmp((char*)attr->children->content,SOAP_1_1_ENC_NAMESPACE) != 0) {
					soap_server_fault("Client", "Unknown data encoding style", NULL, NULL, NULL);
				}
			}
			attr = attr->next;
		}
		trav = head->children;
		while (trav != NULL) {
			if (trav->type == XML_ELEMENT_NODE) {
				xmlNodePtr hdr_func = trav;
				int mustUnderstand = 0;

				if (*version == SOAP_1_1) {
					attr = get_attribute_ex(hdr_func->properties,"encodingStyle",SOAP_1_1_ENV_NAMESPACE);
					if (attr && strcmp((char*)attr->children->content,SOAP_1_1_ENC_NAMESPACE) != 0) {
						soap_server_fault("Client","Unknown Data Encoding Style", NULL, NULL, NULL);
					}
					attr = get_attribute_ex(hdr_func->properties,"actor",envelope_ns);
					if (attr != NULL) {
						if (strcmp((char*)attr->children->content,SOAP_1_1_ACTOR_NEXT) != 0 &&
						    (actor == NULL || strcmp((char*)attr->children->content,actor) != 0)) {
						  goto ignore_header;
						}
					}
				} else if (*version == SOAP_1_2) {
					attr = get_attribute_ex(hdr_func->properties,"encodingStyle",SOAP_1_2_ENV_NAMESPACE);
					if (attr && strcmp((char*)attr->children->content,SOAP_1_2_ENC_NAMESPACE) != 0) {
						soap_server_fault("DataEncodingUnknown","Unknown Data Encoding Style", NULL, NULL, NULL);
					}
					attr = get_attribute_ex(hdr_func->properties,"role",envelope_ns);
					if (attr != NULL) {
						if (strcmp((char*)attr->children->content,SOAP_1_2_ACTOR_UNLIMATERECEIVER) != 0 &&
						    strcmp((char*)attr->children->content,SOAP_1_2_ACTOR_NEXT) != 0 &&
						    (actor == NULL || strcmp((char*)attr->children->content,actor) != 0)) {
						  goto ignore_header;
						}
					}
				}
				attr = get_attribute_ex(hdr_func->properties,"mustUnderstand",envelope_ns);
				if (attr) {
					if (strcmp((char*)attr->children->content,"1") == 0 ||
					    strcmp((char*)attr->children->content,"true") == 0) {
						mustUnderstand = 1;
					} else if (strcmp((char*)attr->children->content,"0") == 0 ||
					           strcmp((char*)attr->children->content,"false") == 0) {
						mustUnderstand = 0;
					} else {
						soap_server_fault("Client","mustUnderstand value is not boolean", NULL, NULL, NULL);
					}
				}
				h = emalloc(sizeof(soapHeader));
				memset(h, 0, sizeof(soapHeader));
				h->mustUnderstand = mustUnderstand;
				h->function = find_function(sdl, hdr_func, &h->function_name);
				if (!h->function && sdl && function && function->binding && function->binding->bindingType == BINDING_SOAP) {
					sdlSoapBindingFunctionHeaderPtr hdr;
					sdlSoapBindingFunctionPtr fnb = (sdlSoapBindingFunctionPtr)function->bindingAttributes;
					if (fnb->input.headers) {
						smart_str key = {0};

						if (hdr_func->ns) {
							smart_str_appends(&key, (char*)hdr_func->ns->href);
							smart_str_appendc(&key, ':');
						}
						smart_str_appendl(&key, Z_STRVAL(h->function_name), Z_STRLEN(h->function_name));
						smart_str_0(&key);
						if ((hdr = zend_hash_find_ptr(fnb->input.headers, key.s)) != NULL) {
							h->hdr = hdr;
						}
						smart_str_free(&key);
					}
				}
				if (h->hdr) {
					h->num_params = 1;
					h->parameters = emalloc(sizeof(zval));
					master_to_zval(&h->parameters[0], h->hdr->encode, hdr_func);
				} else {
					if (h->function && h->function->binding && h->function->binding->bindingType == BINDING_SOAP) {
						sdlSoapBindingFunctionPtr fnb = (sdlSoapBindingFunctionPtr)h->function->bindingAttributes;
						if (fnb->style == SOAP_RPC) {
							hdr_func = hdr_func->children;
						}
					}
					deserialize_parameters(hdr_func, h->function, &h->num_params, &h->parameters);
				}
				ZVAL_NULL(&h->retval);
				if (last == NULL) {
					*headers = h;
				} else {
					last->next = h;
				}
				last = h;
			}
ignore_header:
			trav = trav->next;
		}
	}

	if (function && function->binding && function->binding->bindingType == BINDING_SOAP) {
		sdlSoapBindingFunctionPtr fnb = (sdlSoapBindingFunctionPtr)function->bindingAttributes;
		if (fnb->style == SOAP_RPC) {
			func = func->children;
		}
	} else {
		func = func->children;
	}
	deserialize_parameters(func, function, num_params, parameters);

	encode_finish();

	return function;
}