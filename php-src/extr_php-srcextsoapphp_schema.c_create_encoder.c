#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  xmlChar ;
struct TYPE_15__ {int /*<<< orphan*/  s; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_2__ smart_str ;
typedef  int /*<<< orphan*/  sdlTypePtr ;
typedef  TYPE_3__* sdlPtr ;
typedef  TYPE_4__* encodePtr ;
typedef  int /*<<< orphan*/  encode ;
struct TYPE_14__ {int /*<<< orphan*/  sdl_type; void* type_str; void* ns; } ;
struct TYPE_17__ {int /*<<< orphan*/  to_zval; int /*<<< orphan*/  to_xml; TYPE_1__ details; } ;
struct TYPE_16__ {int /*<<< orphan*/ * encoders; } ;
typedef  int /*<<< orphan*/  HashTable ;

/* Variables and functions */
 int /*<<< orphan*/  delete_encoder ; 
 int /*<<< orphan*/  efree (void*) ; 
 void* emalloc (int) ; 
 void* estrdup (char*) ; 
 int /*<<< orphan*/  memset (TYPE_4__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sdl_guess_convert_xml ; 
 int /*<<< orphan*/  sdl_guess_convert_zval ; 
 int /*<<< orphan*/  smart_str_0 (TYPE_2__*) ; 
 int /*<<< orphan*/  smart_str_appendc (TYPE_2__*,char) ; 
 int /*<<< orphan*/  smart_str_appends (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  smart_str_free (TYPE_2__*) ; 
 TYPE_4__* zend_hash_find_ptr (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zend_hash_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zend_hash_update_ptr (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_4__*) ; 

__attribute__((used)) static encodePtr create_encoder(sdlPtr sdl, sdlTypePtr cur_type, const xmlChar *ns, const xmlChar *type)
{
	smart_str nscat = {0};
	encodePtr enc, enc_ptr;

	if (sdl->encoders == NULL) {
		sdl->encoders = emalloc(sizeof(HashTable));
		zend_hash_init(sdl->encoders, 0, NULL, delete_encoder, 0);
	}
	smart_str_appends(&nscat, (char*)ns);
	smart_str_appendc(&nscat, ':');
	smart_str_appends(&nscat, (char*)type);
	smart_str_0(&nscat);
	if ((enc_ptr = zend_hash_find_ptr(sdl->encoders, nscat.s)) != NULL) {
		enc = enc_ptr;
		if (enc->details.ns) {
			efree(enc->details.ns);
		}
		if (enc->details.type_str) {
			efree(enc->details.type_str);
		}
	} else {
		enc_ptr = NULL;
		enc = emalloc(sizeof(encode));
	}
	memset(enc, 0, sizeof(encode));

	enc->details.ns = estrdup((char*)ns);
	enc->details.type_str = estrdup((char*)type);
	enc->details.sdl_type = cur_type;
	enc->to_xml = sdl_guess_convert_xml;
	enc->to_zval = sdl_guess_convert_zval;

	if (enc_ptr == NULL) {
		zend_hash_update_ptr(sdl->encoders, nscat.s, enc);
	}
	smart_str_free(&nscat);
	return enc;
}