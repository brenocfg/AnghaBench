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

/* Variables and functions */
 int blob_version (char*) ; 
 int getopt (int,char**,char*) ; 
 size_t optind ; 
 int rasign_show_help () ; 

int main(int argc, char **argv) {
	int c;
	int action = 0;
	int rad = 0;
	int json = 0;
	//RSign *sig = r_sign_new ();

	while ((c=getopt (argc, argv, "o:hrsj:iV")) !=-1) {
		switch (c) {
		case 'o':
			//r_sign_option (&sig, optarg);
			break;
		case 's':
			action = c;
			//r_sign_load_file (&sig, optarg);
			break;
		case 'r':
			rad = 1;
			break;
		case 'j':
			json = 1;
			break;
		case 'V':
			return blob_version ("rasign2");
		default:
			return rasign_show_help ();
		}
	}

	if (argv[optind]==NULL)
		return rasign_show_help ();

	//r_sign_list (sig, rad, json);

	switch (action) {
	case 's':
		/* check sigfiles in optarg file */
	//	r_sign_check (&sig, argv[optind]);
		break;
	default:
		/* generate signature file */
		//r_sign_generate (&sig, argv[optind], stdout);
		break;
	}

	//r_sign_free (sig);

	return 0;
}