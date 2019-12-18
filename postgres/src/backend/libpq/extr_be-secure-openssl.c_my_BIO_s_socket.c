#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_23__   TYPE_1__ ;

/* Type definitions */
struct TYPE_23__ {int /*<<< orphan*/  bwrite; int /*<<< orphan*/  bread; } ;
typedef  TYPE_1__ BIO_METHOD ;

/* Variables and functions */
 int BIO_get_new_index () ; 
 int /*<<< orphan*/  BIO_meth_free (TYPE_1__*) ; 
 int /*<<< orphan*/  BIO_meth_get_callback_ctrl (TYPE_1__*) ; 
 int /*<<< orphan*/  BIO_meth_get_create (TYPE_1__*) ; 
 int /*<<< orphan*/  BIO_meth_get_ctrl (TYPE_1__*) ; 
 int /*<<< orphan*/  BIO_meth_get_destroy (TYPE_1__*) ; 
 int /*<<< orphan*/  BIO_meth_get_gets (TYPE_1__*) ; 
 int /*<<< orphan*/  BIO_meth_get_puts (TYPE_1__*) ; 
 TYPE_1__* BIO_meth_new (int,char*) ; 
 int /*<<< orphan*/  BIO_meth_set_callback_ctrl (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BIO_meth_set_create (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BIO_meth_set_ctrl (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BIO_meth_set_destroy (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BIO_meth_set_gets (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BIO_meth_set_puts (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BIO_meth_set_read (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BIO_meth_set_write (TYPE_1__*,int /*<<< orphan*/ ) ; 
 scalar_t__ BIO_s_socket () ; 
 TYPE_1__* malloc (int) ; 
 int /*<<< orphan*/  memcpy (TYPE_1__*,TYPE_1__*,int) ; 
 TYPE_1__* my_bio_methods ; 
 int /*<<< orphan*/  my_sock_read ; 
 int /*<<< orphan*/  my_sock_write ; 

__attribute__((used)) static BIO_METHOD *
my_BIO_s_socket(void)
{
	if (!my_bio_methods)
	{
		BIO_METHOD *biom = (BIO_METHOD *) BIO_s_socket();
#ifdef HAVE_BIO_METH_NEW
		int			my_bio_index;

		my_bio_index = BIO_get_new_index();
		if (my_bio_index == -1)
			return NULL;
		my_bio_methods = BIO_meth_new(my_bio_index, "PostgreSQL backend socket");
		if (!my_bio_methods)
			return NULL;
		if (!BIO_meth_set_write(my_bio_methods, my_sock_write) ||
			!BIO_meth_set_read(my_bio_methods, my_sock_read) ||
			!BIO_meth_set_gets(my_bio_methods, BIO_meth_get_gets(biom)) ||
			!BIO_meth_set_puts(my_bio_methods, BIO_meth_get_puts(biom)) ||
			!BIO_meth_set_ctrl(my_bio_methods, BIO_meth_get_ctrl(biom)) ||
			!BIO_meth_set_create(my_bio_methods, BIO_meth_get_create(biom)) ||
			!BIO_meth_set_destroy(my_bio_methods, BIO_meth_get_destroy(biom)) ||
			!BIO_meth_set_callback_ctrl(my_bio_methods, BIO_meth_get_callback_ctrl(biom)))
		{
			BIO_meth_free(my_bio_methods);
			my_bio_methods = NULL;
			return NULL;
		}
#else
		my_bio_methods = malloc(sizeof(BIO_METHOD));
		if (!my_bio_methods)
			return NULL;
		memcpy(my_bio_methods, biom, sizeof(BIO_METHOD));
		my_bio_methods->bread = my_sock_read;
		my_bio_methods->bwrite = my_sock_write;
#endif
	}
	return my_bio_methods;
}