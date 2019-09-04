#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  size_t ut32 ;
struct TYPE_6__ {scalar_t__ length; int /*<<< orphan*/ * objects; } ;
struct TYPE_8__ {TYPE_1__ list; } ;
struct TYPE_7__ {size_t length; int /*<<< orphan*/ ** elements; } ;
typedef  int /*<<< orphan*/  RX509AlgorithmIdentifier ;
typedef  TYPE_2__ RPKCS7DigestAlgorithmIdentifiers ;
typedef  TYPE_3__ RASN1Object ;

/* Variables and functions */
 scalar_t__ calloc (scalar_t__,int) ; 
 scalar_t__ malloc (int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  r_x509_parse_algorithmidentifier (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool r_pkcs7_parse_digestalgorithmidentifier(RPKCS7DigestAlgorithmIdentifiers *dai, RASN1Object *object) {
	ut32 i;
	if (!dai || !object) {
		return false;
	}
	if (object->list.length > 0) {
		dai->elements = (RX509AlgorithmIdentifier **)calloc (object->list.length, sizeof (RX509AlgorithmIdentifier *));
		if (!dai->elements) {
			return false;
		}
		dai->length = object->list.length;
		for (i = 0; i < dai->length; ++i) {
			// r_x509_parse_algorithmidentifier returns bool,
			// so i have to allocate before calling the function
			dai->elements[i] = (RX509AlgorithmIdentifier *)malloc (sizeof (RX509AlgorithmIdentifier));
			//should i handle invalid memory? the function checks the pointer
			//or it should return if dai->elements[i] == NULL ?
			if (dai->elements[i]) {
				//Memset is needed to initialize to 0 the structure and avoid garbage.
				memset (dai->elements[i], 0, sizeof (RX509AlgorithmIdentifier));
				r_x509_parse_algorithmidentifier (dai->elements[i], object->list.objects[i]);
			}
		}
	}
	return true;
}